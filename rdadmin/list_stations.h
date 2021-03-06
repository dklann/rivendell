// list_stations.h
//
// List Rivendell Workstations
//
//   (C) Copyright 2002-2019 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef LIST_STATIONS_H
#define LIST_STATIONS_H

#include <q3listbox.h>

#include <qlabel.h>
#include <qpushbutton.h>

#include <rddialog.h>

class ListStations : public RDDialog
{
  Q_OBJECT
 public:
  ListStations(QWidget *parent=0);
  ~ListStations();
  QSize sizeHint() const;
  QSizePolicy sizePolicy() const;
  
 private slots:
  void addData();
  void editData();
  void deleteData();
  void doubleClickedData(Q3ListBoxItem *item);
  void closeData();

 protected:
  void resizeEvent(QResizeEvent *e);
  
 private:
  void RefreshList(QString stationname="");
  QLabel *list_title_label;
  Q3ListBox *list_box;
  QPushButton *list_add_button;
  QPushButton *list_edit_button;
  QPushButton *list_delete_button;
  QPushButton *list_close_button;
};


#endif  // LIST_STATIONS_H
