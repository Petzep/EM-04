/*

Copyright (c) 2011, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <QApplication>
#include <QPushButton>

#include "qpiemenu.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QPushButton btn("Right-click me!");
	btn.setWindowTitle("QPieMenu Demo");
	btn.setGeometry(0, 0, 320, 240);
	btn.setContextMenuPolicy(Qt::CustomContextMenu);

	QPieMenu *pieMenu = new QPieMenu(&btn);
	pieMenu->addAction("Drag", QIcon("icons/drag.png"), pieMenu, SLOT(closeMenu()));
	pieMenu->addAction("Zoom", QIcon("icons/zoom.png"), pieMenu, SLOT(closeMenu()));
	pieMenu->addAction("Rotate", QIcon("icons/rotate.png"), pieMenu, SLOT(closeMenu()));
	pieMenu->addAction("Window", QIcon("icons/win_width.png"), pieMenu, SLOT(closeMenu()));
	pieMenu->addAction("Draw ROI", QIcon("icons/roi_draw.png"), pieMenu, SLOT(closeMenu()));
	pieMenu->addAction("Delete ROI", QIcon("icons/roi_delete.png"), pieMenu, SLOT(closeMenu()));
	pieMenu->addAction("Edit ROI", QIcon("icons/roi_edit.png"), pieMenu, SLOT(closeMenu()));
	pieMenu->addAction("Move ROI", QIcon("icons/roi_move.png"), pieMenu, SLOT(closeMenu()));

	QPieMenu *roiTypeMenu = new QPieMenu(pieMenu);
	roiTypeMenu->addAction("Rectangle", QIcon("icons/roi_rect.png"), roiTypeMenu, SLOT(closeMenu()));
	roiTypeMenu->addAction("Ellipse", QIcon("icons/roi_ellipse.png"), roiTypeMenu, SLOT(closeMenu()));
	roiTypeMenu->addAction("Lines", QIcon("icons/roi_lines.png"), roiTypeMenu, SLOT(closeMenu()));
	roiTypeMenu->addAction("Polygon", QIcon("icons/roi_poly.png"), roiTypeMenu, SLOT(closeMenu()));
	pieMenu->addMenu("ROI Type", QIcon("icons/roi_type.png"), roiTypeMenu);

	pieMenu->addAction("Rulers", QIcon("icons/rulers.png"), pieMenu, SLOT(closeMenu()));

	QObject::connect(&btn, SIGNAL(customContextMenuRequested(QPoint)), pieMenu, SLOT(showMenu()));
	// QObject::connect(&btn, SIGNAL(clicked()), pieMenu, SLOT(showMenu()));
	btn.show();

	return app.exec();
}
