#ifndef FRUSTUM_POINTS_H
#define FRUSTUM_POINTS_H

namespace Math
{
    /**
     * @brief The FrustumPoints enum. Contains corner points of the frustum.
     */
    enum class FrustumPoints {
        NLT, //!< Near left top
        NLB, //!< Near right bottom
        NRB, //!< Near right top
        NRT, //!< Near right top
        FLT, //!< Far left top
        FLB, //!< Far left bottom
        FRB, //!< Far right bottom
        FRT	 //!< Far right top
    };

    constexpr int GetIndex(const FrustumPoints& p)
    {
        return (int)p;
    }
}

#endif // FRUSTUM_POINTS_H
