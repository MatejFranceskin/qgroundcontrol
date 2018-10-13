/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "TerrainRequest.h"
#include "QGCMapEngine.h"
#include "QGeoMapReplyQGC.h"
#include "QGCApplication.h"
#include "TerrainQuery.h"

void TerrainRequest::process(mavlink_terrain_request_t& terrainRequest)
{
     QMutexLocker ml(&_responseListMutex);

     // Discard pending data responses and start from the beginning. Vehicle has timed out on previous request.
     _responseList.clear();

     uint64_t mask = terrainRequest.mask;
     uint8_t gridbit = 0;
     while (mask > 0) {
         if ((mask & 1) > 0) {
             mavlink_terrain_data_t data;
             data.grid_spacing = terrainRequest.grid_spacing;
             data.gridbit = gridbit;
             data.lat = terrainRequest.lat;
             data.lon = terrainRequest.lon;
            _responseList.append(data);
         }
         gridbit++;
         mask >>= 1;
     }

     nextRequest();
}

void TerrainRequest::nextRequest()
{
    if (_responseList.empty()) {
        _current_terrain_query_valid = false;
        return;
    }
    _current_terrain_query = _responseList.first();
    _current_terrain_query_valid = true;
    _responseList.removeFirst();

    TerrainAtCoordinateQuery* terrain = new TerrainAtCoordinateQuery(this);
    connect(terrain, &TerrainAtCoordinateQuery::terrainDataReceived, this, &TerrainRequest::terrainHeightReceived);
    QList<QGeoCoordinate> rgCoord;
    QGeoCoordinate coord(_current_terrain_query.lat, _current_terrain_query.lon);
    int f = _current_terrain_query.gridbit % 8;
    int n = _current_terrain_query.gridbit / 8;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            QGeoCoordinate c = coord.atDistanceAndAzimuth(_current_terrain_query.grid_spacing * (f * 4 + j), 90);
            rgCoord.append(c.atDistanceAndAzimuth(_current_terrain_query.grid_spacing * (n * 4 + i), 0));
        }
    }

    terrain->requestData(rgCoord);
}

void TerrainRequest::terrainHeightReceived(bool success, QList<double> heights)
{
    QMutexLocker ml(&_responseListMutex);

    if (success && _current_terrain_query_valid) {
        for (int i = 0; i < heights.count() && i < 16; ++i)
            _current_terrain_query.data[i] = static_cast<int16_t>(round(heights[i]));
        reinterpret_cast<Vehicle *>(parent())->_sendTerrainDataToVehicle(_current_terrain_query);
    }
    nextRequest();
    sender()->deleteLater();
}

