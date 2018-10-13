/****************************************************************************
 *
 *   (c) 2017 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "QGCLoggingCategory.h"
#include "MAVLinkProtocol.h"

#include <QObject>
#include <QGeoCoordinate>

Q_DECLARE_LOGGING_CATEGORY(TerrainQueryLog)
Q_DECLARE_LOGGING_CATEGORY(TerrainQueryVerboseLog)

/// Base class for offline/online terrain queries
class TerrainRequest : public QObject
{
    Q_OBJECT

public:
    TerrainRequest(QObject* parent) :
        QObject(parent),
        _responseListMutex(),
        _responseList()
    { }

    void process(mavlink_terrain_request_t& terrainRequest);

private:
    QMutex _responseListMutex;
    QList<mavlink_terrain_data_t> _responseList;
    mavlink_terrain_data_t _current_terrain_query;
    bool _current_terrain_query_valid = false;

    void terrainHeightReceived(bool success, QList<double> heights);

    void nextRequest();
};
