/****************************************************************************
 *
 *   (c) 2018 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @brief Unit test for TerrainRequest functionality.
///
///     @author Matej Frančeškin <Matej.Franceskin@gmail.com>

#include "TerrainRequestTest.h"

void TerrainRequestTest::_request_test()
{
    QGeoCoordinate coord(47.364869, 8.594398, 0.0);

    double expectedX = -1281.152128182419801305514;
    double expectedY = 3486.949719522415307437768;
    double expectedZ = 0;

    double x, y, z;

    QCOMPARE(x, expectedX);
    QCOMPARE(y, expectedY);
    QCOMPARE(z, expectedZ);
}
