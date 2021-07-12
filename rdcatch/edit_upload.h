// edit_upload.h
//
// Edit a Rivendell Upload Event
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

#ifndef EDIT_UPLOAD_H
#define EDIT_UPLOAD_H

#include <QCheckBox>
#include <QDateTimeEdit>
#include <QLabel>
#include <QSpinBox>

#include <rdcombobox.h>
#include <rdcut_dialog.h>
#include <rddeck.h>
#include <rddialog.h>
#include <rdfeedlistmodel.h>
#include <rdrecording.h>

class EditUpload : public RDDialog
{
 Q_OBJECT
 public:
 EditUpload(int id,std::vector<int> *adds,QString *filter,QWidget *parent=0);
  ~EditUpload();
  QSize sizeHint() const;
  QSizePolicy sizePolicy() const;
  
 private slots:
  void stationChangedData(const QString &str);
  void feedChangedData(int index);
  void urlChangedData(const QString &str);
  void selectCartData();
  void setFormatData();
  void normalizeCheckData(bool state);
  void saveasData();
  void okData();
  void cancelData();
  
 protected:
  void resizeEvent(QResizeEvent *e);
  void keyPressEvent(QKeyEvent *);
  void closeEvent(QCloseEvent *e);
  
 private:
  void Save();
  bool CheckEvent(bool include_myself);
  bool CheckFormat();
  RDDeck *edit_deck;
  RDCutDialog *edit_cut_dialog;
  RDRecording *edit_recording;
  RDSettings edit_settings;
  QCheckBox *edit_active_button;
  QLabel *edit_active_label;
  QLabel *edit_station_label;
  RDComboBox *edit_station_box;
  QLabel *edit_starttime_label;
  QTimeEdit *edit_starttime_edit;
  QLabel *edit_feed_label;
  QComboBox *edit_feed_box;
  RDFeedListModel *edit_feed_model;
  QLabel *edit_description_label;
  QLineEdit *edit_description_edit;
  QPushButton *edit_source_select_button;
  QLabel *edit_url_label;
  QLineEdit *edit_url_edit;
  QLabel *edit_username_label;
  QLineEdit *edit_username_edit;
  QLabel *edit_password_label;
  QLineEdit *edit_password_edit;
  QString edit_cutname;
  QLabel *edit_source_label;
  QLineEdit *edit_source_edit;
  QLabel *edit_format_label;
  QLineEdit *edit_format_edit;
  QPushButton *edit_format_set_button;
  QCheckBox *edit_normalize_box;
  QLabel *edit_normalize_label;
  QLabel *edit_normalize_level_label;
  QSpinBox *edit_normalize_spin;
  QLabel *edit_normalize_unit;
  QCheckBox *edit_metadata_box;
  QLabel *edit_metadata_label;
  QCheckBox *edit_sun_button;
  QLabel *edit_sun_label;
  QCheckBox *edit_mon_button;
  QLabel *edit_mon_label;
  QCheckBox *edit_tue_button;
  QLabel *edit_tue_label;
  QCheckBox *edit_wed_button;
  QLabel *edit_wed_label;
  QCheckBox *edit_thu_button;
  QLabel *edit_thu_label;
  QCheckBox *edit_fri_button;
  QLabel *edit_fri_label;
  QCheckBox *edit_sat_button;
  QLabel *edit_sat_label;
  QLabel *edit_eventoffset_label;
  QSpinBox *edit_eventoffset_spin;
  QLabel *edit_eventoffset_unit_label;
  QCheckBox *edit_oneshot_box;
  QLabel *edit_oneshot_label;
  QPushButton *event_saveas_button;
  QPushButton *event_ok_button;
  QPushButton *event_cancel_button;
  std::vector<int> *edit_added_events;
  QString *edit_filter;
  QString edit_group;
  QString edit_schedcode;
};


#endif  // EDIT_UPLOAD_H
