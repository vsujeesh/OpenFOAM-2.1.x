/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::pointData

Description
    Variant of pointEdgePoint with some transported additional data.
    WIP - should be templated on data like wallDistData.
    Passive vector v_ is not a coordinate (so no enterDomain/leaveDomain
    transformation needed)

SourceFiles
    pointDataI.H
    pointData.C

\*---------------------------------------------------------------------------*/

#ifndef pointData_H
#define pointData_H

#include "pointEdgePoint.H"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class pointData Declaration
\*---------------------------------------------------------------------------*/

class pointData
:
    public pointEdgePoint
{
    // Private data

        //- additional information.
        scalar s_;

        //- additional information.
        vector v_;

public:

    // Constructors

        //- Construct null
        inline pointData();

        //- Construct from origin, distance
        inline pointData
        (
            const point& origin,
            const scalar distSqr,
            const scalar s,
            const vector& v
        );

        //- Construct as copy
        inline pointData(const pointData&);


    // Member Functions

        // Access

            inline scalar s() const;

            inline const vector& v() const;


        // Needed by meshWave

            //- Apply rotation matrix to origin
            template<class TrackingData>
            inline void transform
            (
                const tensor& rotTensor,
                TrackingData& td
            );

            //- Influence of edge on point
            template<class TrackingData>
            inline bool updatePoint
            (
                const polyMesh& mesh,
                const label pointI,
                const label edgeI,
                const pointData& edgeInfo,
                const scalar tol,
                TrackingData& td
            );

            //- Influence of different value on same point.
            //  Merge new and old info.
            template<class TrackingData>
            inline bool updatePoint
            (
                const polyMesh& mesh,
                const label pointI,
                const pointData& newPointInfo,
                const scalar tol,
                TrackingData& td
            );

            //- Influence of different value on same point.
            //  No information about current position whatsoever.
            template<class TrackingData>
            inline bool updatePoint
            (
                const pointData& newPointInfo,
                const scalar tol,
                TrackingData& td
            );

            //- Influence of point on edge.
            template<class TrackingData>
            inline bool updateEdge
            (
                const polyMesh& mesh,
                const label edgeI,
                const label pointI,
                const pointData& pointInfo,
                const scalar tol,
                TrackingData& td
            );

    // IOstream Operators

        friend Ostream& operator<<(Ostream&, const pointData&);
        friend Istream& operator>>(Istream&, pointData&);
};


//- Data associated with pointData as contiguous as pointEdgePoint
template<>
inline bool contiguous<pointData>()
{
    return contiguous<pointEdgePoint>();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "pointDataI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
