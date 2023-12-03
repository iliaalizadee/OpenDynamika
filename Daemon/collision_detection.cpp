#include "collision_detection.h"
#include "vector_operations.h"


bool lineIntersectsWithSurface(Line line, Surface surface){

    

    if(dot(line.end - line.start, surface.normalVector) == 0){
        return false;
    }

    Vec3D p1RelativeToSurface(line.start - surface.CoS);
    Vec3D p2RelativeToSurface(line.end - surface.CoS);
    Vec3D arbitraryTriangleEdgeVector(surface.surfaceBoundary.vertices[1] - surface.surfaceBoundary.vertices[0]);
    Vec3D arbitraryThirdDimension(cross(surface.normalVector, arbitraryTriangleEdgeVector));

    Point p1MappedToSurface(
        Position(
            dot(p1RelativeToSurface, arbitraryTriangleEdgeVector),
            dot(p1RelativeToSurface, arbitraryThirdDimension),
            0
        )
    );

    Point p2MappedToSurface(
        Position(
            dot(p2RelativeToSurface, arbitraryTriangleEdgeVector),
            dot(p2RelativeToSurface, arbitraryThirdDimension),
            0
        )
    );

    
    float intersectionWeight(dot(p1RelativeToSurface, surface.normalVector)/
    (dot(p1RelativeToSurface, surface.normalVector) + dot(p2RelativeToSurface, surface.normalVector)));


    Point intersectionPointRelativeToSurface(
        Position(
            p1MappedToSurface.pos.x + intersectionWeight * (p2MappedToSurface.pos.x - p2MappedToSurface.pos.x),
            p1MappedToSurface.pos.y + intersectionWeight * (p2MappedToSurface.pos.y - p2MappedToSurface.pos.y),
            0
        )
    );
}