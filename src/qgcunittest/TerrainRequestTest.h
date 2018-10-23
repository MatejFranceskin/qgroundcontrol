/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

/// @file
///     @brief Unit test for TerrainRequest functionality.
///
///     @author Matej Frančeškin <Matej.Franceskin@gmail.com>

#ifndef TERRAIN_REQUEST_H
#define TERRAIN_REQUEST_H

#include "UnitTest.h"
#include "TerrainRequest.h"

class TerrainRequestTest : public UnitTest
{
    Q_OBJECT

public:
    TerrainRequestTest(void)
        : _origin(47.3764, 8.5481, 0.0) /// Use ETH campus (47.3764° N, 8.5481° E)
    { }

private slots:
    void _request_test();

private:
    QGeoCoordinate _origin;
};

#endif // TERRAIN_REQUEST_H
