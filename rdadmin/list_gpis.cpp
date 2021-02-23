// list_gpis.cpp
//
// List Rivendell GPIOs
//
//   (C) Copyright 2002-2021 Fred Gleason <fredg@paravelsystems.com>
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

#include <rd.h>
#include <rdapplication.h>
#include <rddb.h>
#include <rdescape_string.h>

#include "globals.h"
#include "list_gpis.h"

ListGpis::ListGpis(RDMatrix *matrix,RDMatrix::GpioType type,QWidget *parent)
  : RDDialog(parent)
{
  QString list_label;

  list_matrix=matrix;
  list_type=type;
  switch(type) {
  case RDMatrix::GpioInput:
    list_label=tr("GPI Lines");
    setWindowTitle("RDAdmin - "+tr("List GPIs"));
    break;

  case RDMatrix::GpioOutput:
    list_label=tr("GPO Lines");
    setWindowTitle("RDAdmin - "+tr("List GPOs"));
    break;
  }

  //
  // Fix the Window Size
  //
  setMinimumSize(sizeHint());

  //
  // Dialogs
  //
  list_edit_gpi_dialog=new EditGpi(this);

  //
  // Gpis List Box
  //
  list_list_view=new RDTableView(this);
  list_list_label=new QLabel(list_label,this);
  list_list_label->setFont(labelFont());
  list_list_model=new RDGpioListModel(matrix,type,this);
  list_list_model->setFont(defaultFont());
  list_list_model->setPalette(palette());
  list_list_view->setModel(list_list_model);
  connect(list_list_view,SIGNAL(doubleClicked(const QModelIndex &)),
	  this,SLOT(doubleClickedData(const QModelIndex &)));
  connect(list_list_model,SIGNAL(modelReset()),
	  list_list_view,SLOT(resizeColumnsToContents()));
  list_list_view->resizeColumnsToContents();

  //
  //  Edit Button
  //
  list_edit_button=new QPushButton(this);
  list_edit_button->setFont(buttonFont());
  list_edit_button->setText(tr("&Edit"));
  connect(list_edit_button,SIGNAL(clicked()),this,SLOT(editData()));

  //
  //  Close Button
  //
  list_close_button=new QPushButton(this);
  list_close_button->setFont(buttonFont());
  list_close_button->setText(tr("&Close"));
  connect(list_close_button,SIGNAL(clicked()),this,SLOT(closeData()));
}


ListGpis::~ListGpis()
{
  delete list_edit_gpi_dialog;
}


QSize ListGpis::sizeHint() const
{
  return QSize(600,400);
} 


QSizePolicy ListGpis::sizePolicy() const
{
  return QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


void ListGpis::editData()
{
  QModelIndexList rows=list_list_view->selectionModel()->selectedRows();

  if(rows.size()!=1) {
    return;
  }
  if(list_edit_gpi_dialog->
     exec(list_type,list_list_model->lineId(rows.first()))) {
    list_list_model->refresh(rows.first());
  }
}


void ListGpis::doubleClickedData(const QModelIndex &index)
{
  editData();
}


void ListGpis::closeData()
{
  done(true);
}


void ListGpis::resizeEvent(QResizeEvent *e)
{
  list_list_view->setGeometry(10,24,size().width()-20,size().height()-94);
  list_list_label->setGeometry(14,5,85,19);
  list_edit_button->setGeometry(10,size().height()-60,80,50);
  list_close_button->setGeometry(size().width()-90,size().height()-60,80,50);
}
