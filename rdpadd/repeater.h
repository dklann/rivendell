// repeater.h
//
// Rivendell PAD Data Repeater
//
//   (C) Copyright 2018-2024 Fred Gleason <fredg@paravelsystems.com>
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

#ifndef REPEATER_H
#define REPEATER_H

#include <QMap>
#include <QObject>
#include <QSignalMapper>
#include <QTcpServer>
#include <QTcpSocket>

#include <rdjsonframer.h>
#include <rdunixserver.h>

#include "repeater.h"

class Repeater : public QObject
{
  Q_OBJECT
 public:
  Repeater(const QString &src_unix_addr,uint16_t serv_port,QObject *parent=0);
  QString sourceUnixAddress() const;
  uint16_t serverPort() const;

 private slots:
  void newClientConnectionData();
  void clientDisconnected(int id);
  void newSourceConnectionData();
  void sourceDisconnected(int id);
  void sendUpdate(const QByteArray &jdoc);

 private:
  uint16_t pad_server_port;
  QString pad_source_unix_address;
  QSignalMapper *pad_client_disconnect_mapper;
  QTcpServer *pad_client_server;
  QMap<int,QTcpSocket *> pad_client_sockets;
  QSignalMapper *pad_source_disconnect_mapper;
  RDUnixServer *pad_source_server;
  QMap<int,RDJsonFramer *> pad_framers;
};


#endif  // REPEATER_H
