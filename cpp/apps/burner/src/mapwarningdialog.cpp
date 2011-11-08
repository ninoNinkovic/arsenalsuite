
/*
 *
 * Copyright 2003 Blur Studio Inc.
 *
 * This file is part of Arsenal.
 *
 * Arsenal is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Arsenal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arsenal; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*
 * $Id$
 */

#include <qtimer.h>

#include "blurqt.h"
#include "iniconfig.h"

#include "mapwarningdialog.h"

TimedDialog::TimedDialog( QWidget * parent, const QString & title, const QString & message, const QString & dontShowKey, int timeout )
: QDialog( parent )
, mConfigKey( dontShowKey )
{
	setupUi( this );
	setWindowTitle( title );
	mWarningLabel->setText( message );
	QTimer::singleShot( timeout * 1000, this, SLOT( accept() ) );
}

void TimedDialog::accept()
{
	if( mDoNotShowCheck->isChecked() ) {
		userConfig().writeBool( mConfigKey, false );
		userConfig().writeToFile();
	}
	QDialog::accept();
}
