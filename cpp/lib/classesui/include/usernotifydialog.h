/*
 *
 * Copyright 2003, 2004 Blur Studio Inc.
 *
 * This file is part of the Resin software package.
 *
 * Resin is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Resin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Resin; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef USER_NOTIFY_H
#define USER_NOTIFY_H

#include <qdialog.h>

#include "classesui.h"

#include "element.h"
#include "employee.h"
#include "user.h"
#include "assettype.h"
#include "ui_usernotifyui.h"

class CLASSESUI_EXPORT UserNotifyDialog : public QDialog, public Ui::UserNotifyUI
{
Q_OBJECT
public:
	UserNotifyDialog( QWidget * parent=0 );

	void setUsers( UserList );
	UserList userList() const;

    void setMainUserList( const EmployeeList & );

    void refreshList();

public slots:

	void addUser();
	void removeUser();

    void setUserInfo( const QString & );
	
protected:

	AssetType mDefaultAssetType;
	AssetType mAssetTypeFilter;

    EmployeeList mMainUserList;	
	QMap <QString,User> mAvailable;
	QMap <QString,User> mSelected;
	QMap <QString,AssetType> mAssetTypeMap;

	User mSelectedUser;
};

#endif // USER_NOTIFY_H

