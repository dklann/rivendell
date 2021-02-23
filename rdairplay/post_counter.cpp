// post_counter.cpp
//
// The post counter widget for Rivendell
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

#include <qpixmap.h>
#include <qpainter.h>

#include <rdapplication.h>

#include "colors.h"
#include "post_counter.h"

PostCounter::PostCounter(QWidget *parent)
  : RDPushButton(parent)
{
  post_running=false;
  post_time_format="hh:mm:ss";
  post_time=QTime();
  post_offset=0;
  post_offset_valid=false;

  //
  // Generate Palettes
  //
  post_idle_palette=palette();
  post_early_palette=
    QPalette(QColor(POSTPOINT_EARLY_COLOR),palette().color(QPalette::Background));
  post_ontime_palette=
    QPalette(QColor(POSTPOINT_ONTIME_COLOR),palette().color(QPalette::Background));
  post_late_palette=
    QPalette(QColor(POSTPOINT_LATE_COLOR),palette().color(QPalette::Background));

  post_offset = 0;
  UpdateDisplay();
}

void PostCounter::setTimeMode(RDAirPlayConf::TimeMode mode)
{
  switch(mode) {
  case RDAirPlayConf::TwentyFourHour:
    post_time_format="hh:mm:ss";
    break;

  case RDAirPlayConf::TwelveHour:
    post_time_format="h:mm:ss ap";
    break;
  }
  UpdateDisplay();
}

QSize PostCounter::sizeHint() const
{
  return QSize(200,60);
}


QSizePolicy PostCounter::sizePolicy() const
{
  return QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


void PostCounter::setPostPoint(QTime point,int offset,bool offset_valid,
			       bool running)
{
  post_time=point;
  post_offset=offset;
  post_offset_valid=offset_valid;
  post_running=running;
  post_set_time=QTime::currentTime();
  UpdateDisplay();
}


void PostCounter::tickCounter()
{
  if(!post_running) {
    UpdateDisplay();
  }
}


void PostCounter::setEnabled(bool state)
{
  QWidget::setEnabled(state);
  UpdateDisplay();
}


void PostCounter::setDisabled(bool state)
{
  setEnabled(!state);
}


void PostCounter::keyPressEvent(QKeyEvent *e)
{
  e->ignore();
}


void PostCounter::UpdateDisplay()
{
  QColor color=palette().color(QPalette::Background);
  QColor system_button_text_color=palette().buttonText().color();
  QString str;
  QString point;
  QString state;
  QTime current_time=
    QTime::currentTime().addMSecs(rda->station()->timeOffset());
  int offset=post_offset;
  if(!post_running) {
    offset-=current_time.msecsTo(post_set_time);
  }

  if(isEnabled()&&(!post_time.isNull())) {
    point= trUtf8("Next Timed Start") + " [" + post_time.toString(post_time_format) + "]";

    if(post_offset_valid) {
      if(offset<-POST_COUNTER_MARGIN) {
	state="-"+QTime().addMSecs(-offset).toString();
	setPalette(post_early_palette);
	color=POSTPOINT_EARLY_COLOR;
      }
      else {
	if(offset>POST_COUNTER_MARGIN) {
	  state="+"+QTime().addMSecs(offset).toString();
	  setPalette(post_late_palette);
	  color=POSTPOINT_LATE_COLOR;
	}
	else {
	  state=tr("On Time");
	  setPalette(post_ontime_palette);
	  color=POSTPOINT_ONTIME_COLOR;
	}
      }
      system_button_text_color=Qt::color1;
    }
    else {
      state="--------";
      setPalette(post_idle_palette);
    }
  }
  else {     // No postpoint/disabled
    point=tr("Next Timed Start [--:--:--]");
    state="--------";
    setPalette(post_idle_palette);
  }
  QPixmap pix(size().width()-2,size().height()-2);
  QPainter *p=new QPainter(&pix);
  p->fillRect(0,0,size().width()-2,size().height()-2,color);
  p->setPen(QColor(system_button_text_color));
  p->setFont(subLabelFont());
  p->drawText((size().width()-2-p->
	       fontMetrics().width(point))/2,22,point);
  p->setFont(bannerFont());
  p->drawText((size().width()-2-p->
	       fontMetrics().width(state))/2,48,state);
  p->end();
  delete p;
  setIcon(pix);    
}
