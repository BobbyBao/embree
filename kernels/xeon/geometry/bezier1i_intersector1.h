// ======================================================================== //
// Copyright 2009-2014 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "bezier1i.h"
#include "bezier_intersector1.h"

namespace embree
{
  template<bool list>
  struct Bezier1iIntersector1
  {
    typedef Bezier1i Primitive;
    typedef BezierIntersector1::Precalculations Precalculations;

    static __forceinline void intersect(Precalculations& pre, Ray& ray, const Primitive& curve, void* geom) 
    {
      Scene* scene = (Scene*) geom;
      const BezierCurves* in = (BezierCurves*) scene->get(curve.geomID<list>());
      const Vec3fa a0 = in->vertex(curve.vertexID+0,0);
      const Vec3fa a1 = in->vertex(curve.vertexID+1,0);
      const Vec3fa a2 = in->vertex(curve.vertexID+2,0);
      const Vec3fa a3 = in->vertex(curve.vertexID+3,0);
      BezierIntersector1::intersect(ray,pre,a0,a1,a2,a3,curve.geomID<list>(),curve.primID<list>(),geom);
    }

    static __forceinline bool occluded(Precalculations& pre, Ray& ray, const Primitive& curve, void* geom) 
    {
      Scene* scene = (Scene*) geom;
      const BezierCurves* in = (BezierCurves*) scene->get(curve.geomID<list>());
      const Vec3fa a0 = in->vertex(curve.vertexID+0,0);
      const Vec3fa a1 = in->vertex(curve.vertexID+1,0);
      const Vec3fa a2 = in->vertex(curve.vertexID+2,0);
      const Vec3fa a3 = in->vertex(curve.vertexID+3,0);
      return BezierIntersector1::occluded(ray,pre,a0,a1,a2,a3,curve.geomID<list>(),curve.primID<list>(),geom);
    }
  };
  
  template<bool list>
  struct Bezier1iIntersector1MB
  {
    typedef Bezier1iMB Primitive;
    typedef BezierIntersector1::Precalculations Precalculations;

    static __forceinline void intersect(Precalculations& pre, Ray& ray, const Primitive& curve, void* geom)
    {
      Scene* scene = (Scene*) geom;
      const BezierCurves* in = (BezierCurves*) scene->get(curve.geomID<list>());
      const Vec3fa a0 = in->vertex(curve.vertexID+0,0);
      const Vec3fa a1 = in->vertex(curve.vertexID+1,0);
      const Vec3fa a2 = in->vertex(curve.vertexID+2,0);
      const Vec3fa a3 = in->vertex(curve.vertexID+3,0);
      const Vec3fa b0 = in->vertex(curve.vertexID+0,1);
      const Vec3fa b1 = in->vertex(curve.vertexID+1,1);
      const Vec3fa b2 = in->vertex(curve.vertexID+2,1);
      const Vec3fa b3 = in->vertex(curve.vertexID+3,1);
      const float t0 = 1.0f-ray.time, t1 = ray.time;
      const Vec3fa p0 = t0*a0 + t1*b0;
      const Vec3fa p1 = t0*a1 + t1*b1;
      const Vec3fa p2 = t0*a2 + t1*b2;
      const Vec3fa p3 = t0*a3 + t1*b3;
      BezierIntersector1::intersect(ray,pre,p0,p1,p2,p3,curve.geomID<list>(),curve.primID<list>(),geom);
    }

    static __forceinline bool occluded(Precalculations& pre, Ray& ray, const Primitive& curve, void* geom) 
    {
      Scene* scene = (Scene*) geom;
      const BezierCurves* in = (BezierCurves*) scene->get(curve.geomID<list>());
      const Vec3fa a0 = in->vertex(curve.vertexID+0,0);
      const Vec3fa a1 = in->vertex(curve.vertexID+1,0);
      const Vec3fa a2 = in->vertex(curve.vertexID+2,0);
      const Vec3fa a3 = in->vertex(curve.vertexID+3,0);
      const Vec3fa b0 = in->vertex(curve.vertexID+0,1);
      const Vec3fa b1 = in->vertex(curve.vertexID+1,1);
      const Vec3fa b2 = in->vertex(curve.vertexID+2,1);
      const Vec3fa b3 = in->vertex(curve.vertexID+3,1);
      const float t0 = 1.0f-ray.time, t1 = ray.time;
      const Vec3fa p0 = t0*a0 + t1*b0;
      const Vec3fa p1 = t0*a1 + t1*b1;
      const Vec3fa p2 = t0*a2 + t1*b2;
      const Vec3fa p3 = t0*a3 + t1*b3;
      return BezierIntersector1::occluded(ray,pre,p0,p1,p2,p3,curve.geomID<list>(),curve.primID<list>(),geom);
    }
  };
}
