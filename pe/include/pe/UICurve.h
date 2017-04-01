#pragma once
#include <Urho3D/UI/Sprite.h>
#include "Urho3D/UI/UIBatch.h"

class URHO3D_API UICurve : public Urho3D::Sprite
{
   URHO3D_OBJECT(UICurve, Sprite)
public:
   UICurve(Urho3D::Context* context);
   ~UICurve() {};
   ///segments for cuve rendering
   int segments_ = 50;
   ///thickness
   float thickness_ = 3.0f;
   ///flag for redrawing curve
   bool isDirty = true;
   ///define controls pts
   Urho3D::Vector<Urho3D::Vector3> controlPoints;
   /// Return UI rendering batches.
   virtual void GetBatches(Urho3D::PODVector<Urho3D::UIBatch>& batches, Urho3D::PODVector<float>& vertexData, const Urho3D::IntRect& currentScissor);
   void AddCurveSegment(Urho3D::UIBatch& batch, Urho3D::Vector3 a, Urho3D::Vector3 b, Urho3D::Vector3 c, Urho3D::Vector3 d);
   ///fills the path verts vectors from the control points
   void BezierCurve(int segments);
   ///Helper function that offsets the path verts and fills the quads vector
   void OffsetCurve(float thickness);
   ///pts defining segmented curve
   Urho3D::Vector<Urho3D::Vector3> pathVerts;
   ///quads that render the curve, by offsetting or filling it
   Urho3D::Vector<Urho3D::Vector3> pathQuads;
   ///update path and quads
   void UpdatePath();
   ///Set and end point
   void SetEndPoint(Urho3D::Vector3 newPos, bool moveTangent=true);
   ///Set start point
   void SetStartPoint(Urho3D::Vector3 newPos, bool moveTangent = true);
};
