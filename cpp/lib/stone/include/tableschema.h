
/*
 *
 * Copyright 2003 Blur Studio Inc.
 *
 * This file is part of libstone.
 *
 * libstone is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libstone is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libstone; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*
 * $Id$
 */

#ifndef TABLE_SCHEMA_H
#define TABLE_SCHEMA_H

#include <qlist.h>
#include <qstring.h>
#include <qobject.h>

#include "field.h"
#include "indexschema.h"

namespace Stone {
class Schema;
class Field;
class Table;
class IndexSchema;
class Record;
class RecordList;
class Trigger;

class STONE_EXPORT TableSchema : public QObject
{
Q_OBJECT
public:
	TableSchema( Schema * schema );
	virtual ~TableSchema();
	
	Schema * schema() const { return mSchema; }

	/// Returns the table instance for this schema associated
	/// with the current database
	Table * table() const;

	/// Returns the parent \ref Table of this table, or
	/// 0 if this table has no parent.
	TableSchema * parent() const;

	/// Sets the parent of this table to \param parent
	void setParent( TableSchema * parent );

	/// Returns the list of tables that this parent inherits,
	/// the parent and each of it's parents recursivly.
	QList<TableSchema*> inherits();

	/// Return the list of \ref Tables that directly inherit
	/// from this table.
	QList<TableSchema*> children();

	/// Returns a list of \ref Tables including this table,
	/// and all tables that directly or indirectly inherit from
	/// this table.
	QList<TableSchema*> tableTree();

	/// Returns true if t is the same table, or
	/// a child table of this
	bool isDescendant( const TableSchema * t ) const;

	Record load( QVariant * v );
	
	virtual Record * createObject( const Record & r );
	
	virtual Record * newObject();

	//
	// Table Information
	//
	/// Sets the name of the table.  Must be called before using
	/// the insert, update, select, remove calls.
	void setTableName(const QString &);
	/// Returns the name of this table, this must match the name
	/// in the database.
	QString tableName();
	
	/// This doesn't have to be set unless
	/// it is different from the table name
	/// it is used for the autogenerated code
	void setClassName( const QString & );
	/// Returns the class name of this table, this
	/// is used for generated c++ classes.
	QString className();

	/// Documentation string in doxygen format
	/// Inserted into generated code
	QString docs() const;
	void setDocs( const QString & docs );

	/// Returns the name of the primary key field
	QString primaryKey();

	/// Returns the index of the primary key field
	/// in this table's list of fields.
	int primaryKeyIndex() { return mPrimaryKeyIndex; }

	/// Returns the number of fields in this table, including
	/// fields that inherit from the parent table.
	uint fieldCount() { return mAllFieldsCache.size(); }

	/// Convencience function returns a list of the names of each field in the table
	QStringList fieldDisplayNames();
	QStringList fieldNames();

	/// Returns a list of all the fields in this table.
	FieldList fields() { return mAllFieldsCache; }

	FieldList defaultSelectFields() const;
	
	/// Returns a list of all the fields in this table that
	/// are not inherited by the parent table.
	FieldList ownedFields();
	
	/// All the columns in the table( including inherited columns )
	/// Returns a list of all the fields, and the local data columns
	/// that are not stored in the database.
	FieldList columns() { return mAllColumnsCache; }

	/// Returns all of the non-inherited columns
	FieldList ownedColumns();

	/// Local variables in the records
	FieldList localVariables();

	/// Non-inherited local variables
	FieldList ownedLocalVariables();

	/// Returns a field by its name, or 0 if there is no
	/// matching field in this table.  This function is
	/// case-insensitive.
	/// If silent is false a warning is printed if the field is not found
	Field * field( const QString & fieldName, bool silent=false );

	/// Returns a field by its position in the field list,
	/// returns 0 if \param pos is out of range.
	Field * field( int pos );
	
	/// Adds a field to this table, takes ownership of the Field
	/// object.
	bool addField( Field * field );

	/// Removes a field from this table, the caller is responsible to
	/// delete the field.
	void removeField( Field * f );

	/// Returns the position of the field with name \param field
	/// in this table's list of fields.
	int fieldPos( const QString & field );

	/// Returns the total number of columns, including local data members
	/// that are not stored in the database.
	uint columnCount();

	void setPreloadEnabled( bool );
	bool isPreloadEnabled() const;

	QString projectPreloadColumn() const;
	void setProjectPreloadColumn( const QString & );

	bool useCodeGen() const;
	void setUseCodeGen( bool useCodeGen );

	bool expireKeyCache() const { return mExpireKeyCache; }
	void setExpireKeyCache( bool ekc ) { mExpireKeyCache = ekc; }

	bool baseOnly() const { return mBaseOnly; }
	void setBaseOnly( bool baseOnly );

	/// Indexes
	///
	IndexSchemaList indexes();
	/// This does not need to be called when creating an
	/// index, because the index calls it itself
	void addIndex( IndexSchema * index );
	void removeIndex( IndexSchema * index, bool dontDelete = false );

	IndexSchema * index( const QString & name ) const;

	uint firstColumnIndex() const { return mFirstColumnIndex; }

	QString diff( TableSchema * table );

	// Takes ownership
	void addTrigger( Trigger * trigger );
	// Ownership given to caller
	void removeTrigger( Trigger * trigger );
	QList<Trigger*> triggers() const;

signals:
	void triggerAdded( Trigger * trigger );
	
protected:
	void recalcFieldPositions( int start = 0, bool skipSelf = false );
	
	void addChild( TableSchema * );
	void removeChild( TableSchema * table );
	
	// Does not propogate to parent tables, done by the Table class itself in processIncoming
	void processCreateTriggers( Record & record );
	RecordList processIncomingTriggers( RecordList incoming );
	RecordList processPreInsertTriggers( RecordList toInsert );
	Record processPreUpdateTriggers( const Record & updated, const Record & before );
	RecordList processPreDeleteTriggers( RecordList toDelete );
	void processPostInsertTriggers( RecordList toInsert );
	void processPostUpdateTriggers( const Record & updated, const Record & before );
	void processPostDeleteTriggers( RecordList toDelete );

	Schema * mSchema;
	TableSchema * mParent;

	QList<TableSchema*> mChildren;

	IndexSchemaList mIndexes;

	uint mColumnCount;
	int mPrimaryKeyIndex;
	uint mFirstColumnIndex;
	QString mTableName, mClassName, mDocs;
	FieldList mFields, mAllFieldsCache, mAllColumnsCache;

	QString mProjectPreloadColumn;
	bool mPreload;
	bool mBaseOnly;

	bool mUseCodeGen;
	bool mExpireKeyCache;

	QList<Trigger*> mTriggers;
	friend class Stone::Table;
};

typedef QList<TableSchema*> TableSchemaList;
typedef QList<TableSchema*>::iterator TableSchemaIter;
typedef QList<TableSchema*>::const_iterator ConstTableSchemaIter;

} //namespace

using Stone::TableSchema;

#include "record.h"

#endif // TABLE_SCHEMA_H
