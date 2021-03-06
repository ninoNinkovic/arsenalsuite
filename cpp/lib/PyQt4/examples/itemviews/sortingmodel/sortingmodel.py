#!/usr/bin/env python

############################################################################
# 
#  Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
# 
#  This file is part of the example classes of the Qt Toolkit.
# 
#  This file may be used under the terms of the GNU General Public
#  License version 2.0 as published by the Free Software Foundation
#  and appearing in the file LICENSE.GPL included in the packaging of
#  self file.  Please review the following information to ensure GNU
#  General Public Licensing requirements will be met:
#  http://www.trolltech.com/products/qt/opensource.html
# 
#  If you are unsure which license is appropriate for your use, please
#  review the following information:
#  http://www.trolltech.com/products/qt/licensing.html or contact the
#  sales department at sales@trolltech.com.
# 
#  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
#  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
# 
############################################################################

import sys
from PyQt4 import QtCore, QtGui

import sortingmodel_rc


class TreeModel(QtCore.QAbstractItemModel):
    def __init__(self, data, parent=None):
        QtCore.QAbstractItemModel.__init__(self, parent)

        rootData = [QtCore.QVariant("Title"), QtCore.QVariant("Summary")]
        self.rootItem = TreeItem(rootData)
        self.setupModelData(data.split("\n"), self.rootItem)
        
    def columnCount(self, parent=QtCore.QModelIndex()):
        if parent.isValid():
            return parent.internalPointer().columnCount()
        else:
            return self.rootItem.columnCount()
        
    def data(self, index, role):
        if not index.isValid():
            return QtCore.QVariant()
        if role != QtCore.Qt.DisplayRole:
            return QtCore.QVariant()
        
        item = index.internalPointer()

        return QtCore.QVariant(item.data(index.column()))
    
    def flags(self, index):
        if not index.isValid():
            return QtCore.Qt.ItemIsEnabled
        
        return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable
    
    def headerData(self, section, orientation, role = QtCore.Qt.DisplayRole):
        if orientation == QtCore.Qt.Horizontal and role == QtCore.Qt.DisplayRole:
            return self.rootItem.data(section)
        
        return QtCore.QVariant()
    
    def index(self, row, column, parent=QtCore.QModelIndex()):
        if not parent.isValid():
            parentItem = self.rootItem
        else:
            parentItem = parent.internalPointer()
        
        childItem = parentItem.child(row)
        if childItem:
            return self.createIndex(row, column, childItem)
        else:
            return QtCore.QModelIndex()
        
    def parent(self, index):
        if not index.isValid():
            return QtCore.QModelIndex()
        
        childItem = index.internalPointer()
        parentItem = childItem.parent()
        
        if parentItem == self.rootItem:
            return QtCore.QModelIndex()
        
        return self.createIndex(parentItem.row(), 0, parentItem)
    
    def rowCount(self, parent = QtCore.QModelIndex()):
        if not parent.isValid():
            parentItem = self.rootItem
        else:
            parentItem = parent.internalPointer()
        
        return parentItem.childCount()
        
    def setupModelData(self, lines, parent):
        parents = [parent]
        indentations = [0]
        
        number = 0
        
        while number < len(lines):
            position = 0
            while position < len(lines[number]):
                if lines[number][position] != " ":
                    break
                position += 1
            
            lineData = lines[number][position:].trimmed()
            
            if not lineData.isEmpty():
                # Read the column data from the rest of the line.
                columnStrings = lineData.split("\t", QtCore.QString.SkipEmptyParts)
                columnData = []
                for column in range(0, len(columnStrings)):
                    columnData.append(columnStrings[column])
                
                if position > indentations[-1]:
                    # The last child of the current parent is now the new parent
                    # unless the current parent has no children.
                    
                    if parents[-1].childCount() > 0:
                        parents.append(parents[-1].child(parents[-1].childCount() - 1))
                        indentations.append(position)
                else:
                    while position < indentations[-1] and len(parents) > 0:
                        parents.pop()
                        indentations.pop()

                # Append a new item to the current parent's list of children.
                parents[-1].appendChild(TreeItem(columnData, parents[-1]))
                
            number += 1


class TreeItem:
    def __init__(self, data, parent=None):
        self.childItems = []

        self.parentItem = parent
        self.itemData = data
        
    def appendChild(self, child):
        self.childItems.append(child)
        
    def child(self, row):
        return self.childItems[row]
    
    def childCount(self):
        return len(self.childItems)
    
    def columnCount(self):
        return len(self.itemData)
    
    def data(self, column):
        return self.itemData[column]
    
    def parent(self):
        return self.parentItem

    def row(self):
        if self.parentItem:
            return self.parentItem.childItems.index(self)

        return 0
    
    
if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    
    file = QtCore.QFile(":/default.txt")
    file.open(QtCore.QIODevice.ReadOnly)
    model = TreeModel(QtCore.QString(file.readAll()))
    file.close()
    
    unsortedView = QtGui.QTreeView()
    unsortedView.setModel(model)
    unsortedView.setWindowTitle("Unsorted Data")
    unsortedView.show()
    
    sortingModel = QtGui.QSortFilterProxyModel()
    sortingModel.setSourceModel(model)
    
    sortedView = QtGui.QTreeView()
    sortedView.setModel(sortingModel)
    sortedView.setWindowTitle("Sorted Data")
    sortedView.header().setSortIndicator(1, QtCore.Qt.AscendingOrder)
    sortedView.header().setSortIndicatorShown(True)
    sortedView.header().setClickable(True)
    sortedView.show()
    
    sys.exit(app.exec_())
