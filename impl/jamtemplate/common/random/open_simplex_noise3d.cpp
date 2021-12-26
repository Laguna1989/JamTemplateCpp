#include "open_simplex_noise3d.hpp"
#include <cmath>
#include <random>

namespace jt {

OpenSimplexNoise3D::OpenSimplexNoise3D()
    : m_stretch3d(-1.0f / 6) //(1/Math.sqrt(3+1)-1)/3;
    , m_squish3d(1.0f / 3) //(Math.sqrt(3+1)-1)/3;
    , m_norm3d(103)
    , m_perm { 0 }
    , m_permGradIndex3d { 0 }
    , m_gradients3d {
        -11,
        4,
        4,
        -4,
        11,
        4,
        -4,
        4,
        11,
        11,
        4,
        4,
        4,
        11,
        4,
        4,
        4,
        11,
        -11,
        -4,
        4,
        -4,
        -11,
        4,
        -4,
        -4,
        11,
        11,
        -4,
        4,
        4,
        -11,
        4,
        4,
        -4,
        11,
        -11,
        4,
        -4,
        -4,
        11,
        -4,
        -4,
        4,
        -11,
        11,
        4,
        -4,
        4,
        11,
        -4,
        4,
        4,
        -11,
        -11,
        -4,
        -4,
        -4,
        -11,
        -4,
        -4,
        -4,
        -11,
        11,
        -4,
        -4,
        4,
        -11,
        -4,
        4,
        -4,
        -11,
    }
{
}

OpenSimplexNoise3D::OpenSimplexNoise3D(std::int64_t seed)
    : OpenSimplexNoise3D()
{
    m_engine.seed(static_cast<unsigned int>(seed));
    short source[256];
    for (short i = 0; i < 256; i++) {
        source[i] = i;
    }
    seed = distr(m_engine);
    seed = distr(m_engine);
    seed = distr(m_engine);
    for (int i = 255; i >= 0; i--) {
        seed = distr(m_engine);
        int r = static_cast<int>((seed + 31) % (i + 1));
        if (r < 0) {
            r += (i + 1);
        }
        m_perm[i] = source[r];
        m_permGradIndex3d[i] = static_cast<short>((m_perm[i] % (m_gradients3d.size() / 3)) * 3);
        source[r] = source[i];
    }
}

float OpenSimplexNoise3D::eval(float x, float y, float z) const
{
    // Place input coordinates on simplectic honeycomb.
    float stretchOffset = (x + y + z) * m_stretch3d;
    float xs = x + stretchOffset;
    float ys = y + stretchOffset;
    float zs = z + stretchOffset;

    // static_cast<int>(floor to get simplectic honeycomb coordinates of rhombohedron (stretched
    // cube) super-cell origin.
    int xsb = static_cast<int>(floor(xs));
    int ysb = static_cast<int>(floor(ys));
    int zsb = static_cast<int>(floor(zs));

    // Skew out to get actual coordinates of rhombohedron origin. We'll need these later.
    float squishOffset = (xsb + ysb + zsb) * m_squish3d;
    float xb = xsb + squishOffset;
    float yb = ysb + squishOffset;
    float zb = zsb + squishOffset;

    // Compute simplectic honeycomb coordinates relative to rhombohedral origin.
    float xins = xs - xsb;
    float yins = ys - ysb;
    float zins = zs - zsb;

    // Sum those together to get a value that determines which region we're in.
    float inSum = xins + yins + zins;

    // Positions relative to origin point.
    float dx0 = x - xb;
    float dy0 = y - yb;
    float dz0 = z - zb;

    // We'll be defining these inside the next block and using them afterwards.
    float dx_ext0, dy_ext0, dz_ext0;
    float dx_ext1, dy_ext1, dz_ext1;
    int xsv_ext0, ysv_ext0, zsv_ext0;
    int xsv_ext1, ysv_ext1, zsv_ext1;

    float value = 0;
    if (inSum <= 1) { // We're inside the tetrahedron (3-Simplex) at (0,0,0)

        // Determine which two of (0,0,1), (0,1,0), (1,0,0) are closest.
        char aPoint = 0x01;
        float aScore = xins;
        char bPoint = 0x02;
        float bScore = yins;
        if (aScore >= bScore && zins > bScore) {
            bScore = zins;
            bPoint = 0x04;
        } else if (aScore < bScore && zins > aScore) {
            aScore = zins;
            aPoint = 0x04;
        }

        // Now we determine the two lattice points not part of the tetrahedron that may contribute.
        // This depends on the closest two tetrahedral vertices, including (0,0,0)
        float wins = 1 - inSum;
        if (wins > aScore
            || wins > bScore) { //(0,0,0) is one of the closest two tetrahedral vertices.
            char c = (bScore > aScore
                    ? bPoint
                    : aPoint); // Our other closest vertex is the closest out of a and b.

            if ((c & 0x01) == 0) {
                xsv_ext0 = xsb - 1;
                xsv_ext1 = xsb;
                dx_ext0 = dx0 + 1;
                dx_ext1 = dx0;
            } else {
                xsv_ext0 = xsv_ext1 = xsb + 1;
                dx_ext0 = dx_ext1 = dx0 - 1;
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0;
                if ((c & 0x01) == 0) {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                } else {
                    ysv_ext0 -= 1;
                    dy_ext0 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1;
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsb;
                zsv_ext1 = zsb - 1;
                dz_ext0 = dz0;
                dz_ext1 = dz0 + 1;
            } else {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz_ext1 = dz0 - 1;
            }
        } else { //(0,0,0) is not one of the closest two tetrahedral vertices.
            char c = static_cast<char>(
                aPoint | bPoint); // Our two extra vertices are determined by the closest two.

            if ((c & 0x01) == 0) {
                xsv_ext0 = xsb;
                xsv_ext1 = xsb - 1;
                dx_ext0 = dx0 - 2 * m_squish3d;
                dx_ext1 = dx0 + 1 - m_squish3d;
            } else {
                xsv_ext0 = xsv_ext1 = xsb + 1;
                dx_ext0 = dx0 - 1 - 2 * m_squish3d;
                dx_ext1 = dx0 - 1 - m_squish3d;
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysb;
                ysv_ext1 = ysb - 1;
                dy_ext0 = dy0 - 2 * m_squish3d;
                dy_ext1 = dy0 + 1 - m_squish3d;
            } else {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy0 - 1 - 2 * m_squish3d;
                dy_ext1 = dy0 - 1 - m_squish3d;
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsb;
                zsv_ext1 = zsb - 1;
                dz_ext0 = dz0 - 2 * m_squish3d;
                dz_ext1 = dz0 + 1 - m_squish3d;
            } else {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz0 - 1 - 2 * m_squish3d;
                dz_ext1 = dz0 - 1 - m_squish3d;
            }
        }

        // Contribution (0,0,0)
        float attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate(xsb + 0, ysb + 0, zsb + 0, dx0, dy0, dz0);
        }

        // Contribution (1,0,0)
        float dx1 = dx0 - 1 - m_squish3d;
        float dy1 = dy0 - 0 - m_squish3d;
        float dz1 = dz0 - 0 - m_squish3d;
        float attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate(xsb + 1, ysb + 0, zsb + 0, dx1, dy1, dz1);
        }

        // Contribution (0,1,0)
        float dx2 = dx0 - 0 - m_squish3d;
        float dy2 = dy0 - 1 - m_squish3d;
        float dz2 = dz1;
        float attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate(xsb + 0, ysb + 1, zsb + 0, dx2, dy2, dz2);
        }

        // Contribution (0,0,1)
        float dx3 = dx2;
        float dy3 = dy1;
        float dz3 = dz0 - 1 - m_squish3d;
        float attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate(xsb + 0, ysb + 0, zsb + 1, dx3, dy3, dz3);
        }
    } else if (inSum >= 2) { // We're inside the tetrahedron (3-Simplex) at (1,1,1)

        // Determine which two tetrahedral vertices are the closest, out of (1,1,0), (1,0,1),
        // (0,1,1) but not (1,1,1).
        char aPoint = 0x06;
        float aScore = xins;
        char bPoint = 0x05;
        float bScore = yins;
        if (aScore <= bScore && zins < bScore) {
            bScore = zins;
            bPoint = 0x03;
        } else if (aScore > bScore && zins < aScore) {
            aScore = zins;
            aPoint = 0x03;
        }

        // Now we determine the two lattice points not part of the tetrahedron that may contribute.
        // This depends on the closest two tetrahedral vertices, including (1,1,1)
        float wins = 3 - inSum;
        if (wins < aScore
            || wins < bScore) { //(1,1,1) is one of the closest two tetrahedral vertices.
            char c = (bScore < aScore
                    ? bPoint
                    : aPoint); // Our other closest vertex is the closest out of a and b.

            if ((c & 0x01) != 0) {
                xsv_ext0 = xsb + 2;
                xsv_ext1 = xsb + 1;
                dx_ext0 = dx0 - 2 - 3 * m_squish3d;
                dx_ext1 = dx0 - 1 - 3 * m_squish3d;
            } else {
                xsv_ext0 = xsv_ext1 = xsb;
                dx_ext0 = dx_ext1 = dx0 - 3 * m_squish3d;
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1 - 3 * m_squish3d;
                if ((c & 0x01) != 0) {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                } else {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0 - 3 * m_squish3d;
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsb + 1;
                zsv_ext1 = zsb + 2;
                dz_ext0 = dz0 - 1 - 3 * m_squish3d;
                dz_ext1 = dz0 - 2 - 3 * m_squish3d;
            } else {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz_ext1 = dz0 - 3 * m_squish3d;
            }
        } else { //(1,1,1) is not one of the closest two tetrahedral vertices.
            char c = static_cast<char>(
                aPoint & bPoint); // Our two extra vertices are determined by the closest two.

            if ((c & 0x01) != 0) {
                xsv_ext0 = xsb + 1;
                xsv_ext1 = xsb + 2;
                dx_ext0 = dx0 - 1 - m_squish3d;
                dx_ext1 = dx0 - 2 - 2 * m_squish3d;
            } else {
                xsv_ext0 = xsv_ext1 = xsb;
                dx_ext0 = dx0 - m_squish3d;
                dx_ext1 = dx0 - 2 * m_squish3d;
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysb + 1;
                ysv_ext1 = ysb + 2;
                dy_ext0 = dy0 - 1 - m_squish3d;
                dy_ext1 = dy0 - 2 - 2 * m_squish3d;
            } else {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy0 - m_squish3d;
                dy_ext1 = dy0 - 2 * m_squish3d;
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsb + 1;
                zsv_ext1 = zsb + 2;
                dz_ext0 = dz0 - 1 - m_squish3d;
                dz_ext1 = dz0 - 2 - 2 * m_squish3d;
            } else {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz0 - m_squish3d;
                dz_ext1 = dz0 - 2 * m_squish3d;
            }
        }

        // Contribution (1,1,0)
        float dx3 = dx0 - 1 - 2 * m_squish3d;
        float dy3 = dy0 - 1 - 2 * m_squish3d;
        float dz3 = dz0 - 0 - 2 * m_squish3d;
        float attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate(xsb + 1, ysb + 1, zsb + 0, dx3, dy3, dz3);
        }

        // Contribution (1,0,1)
        float dx2 = dx3;
        float dy2 = dy0 - 0 - 2 * m_squish3d;
        float dz2 = dz0 - 1 - 2 * m_squish3d;
        float attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate(xsb + 1, ysb + 0, zsb + 1, dx2, dy2, dz2);
        }

        // Contribution (0,1,1)
        float dx1 = dx0 - 0 - 2 * m_squish3d;
        float dy1 = dy3;
        float dz1 = dz2;
        float attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate(xsb + 0, ysb + 1, zsb + 1, dx1, dy1, dz1);
        }

        // Contribution (1,1,1)
        dx0 = dx0 - 1 - 3 * m_squish3d;
        dy0 = dy0 - 1 - 3 * m_squish3d;
        dz0 = dz0 - 1 - 3 * m_squish3d;
        float attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate(xsb + 1, ysb + 1, zsb + 1, dx0, dy0, dz0);
        }
    } else { // We're inside the octahedron (Rectified 3-Simplex) in between.
        float aScore;
        char aPoint;
        bool aIsFurtherSide;
        float bScore;
        char bPoint;
        bool bIsFurtherSide;

        // Decide between point (0,0,1) and (1,1,0) as closest
        float p1 = xins + yins;
        if (p1 > 1) {
            aScore = p1 - 1;
            aPoint = 0x03;
            aIsFurtherSide = true;
        } else {
            aScore = 1 - p1;
            aPoint = 0x04;
            aIsFurtherSide = false;
        }

        // Decide between point (0,1,0) and (1,0,1) as closest
        float p2 = xins + zins;
        if (p2 > 1) {
            bScore = p2 - 1;
            bPoint = 0x05;
            bIsFurtherSide = true;
        } else {
            bScore = 1 - p2;
            bPoint = 0x02;
            bIsFurtherSide = false;
        }

        // The closest out of the two (1,0,0) and (0,1,1) will replace the furthest out of the two
        // decided above, if closer.
        float p3 = yins + zins;
        if (p3 > 1) {
            float score = p3 - 1;
            if (aScore <= bScore && aScore < score) {
                aScore = score;
                aPoint = 0x06;
                aIsFurtherSide = true;
            } else if (aScore > bScore && bScore < score) {
                bScore = score;
                bPoint = 0x06;
                bIsFurtherSide = true;
            }
        } else {
            float score = 1 - p3;
            if (aScore <= bScore && aScore < score) {
                aScore = score;
                aPoint = 0x01;
                aIsFurtherSide = false;
            } else if (aScore > bScore && bScore < score) {
                bScore = score;
                bPoint = 0x01;
                bIsFurtherSide = false;
            }
        }

        // Where each of the two closest points are determines how the extra two vertices are
        // calculated.
        if (aIsFurtherSide == bIsFurtherSide) {
            if (aIsFurtherSide) { // Both closest points on (1,1,1) side

                // One of the two extra points is (1,1,1)
                dx_ext0 = dx0 - 1 - 3 * m_squish3d;
                dy_ext0 = dy0 - 1 - 3 * m_squish3d;
                dz_ext0 = dz0 - 1 - 3 * m_squish3d;
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb + 1;

                // Other extra point is based on the shared axis.
                char c = static_cast<char>(aPoint & bPoint);
                if ((c & 0x01) != 0) {
                    dx_ext1 = dx0 - 2 - 2 * m_squish3d;
                    dy_ext1 = dy0 - 2 * m_squish3d;
                    dz_ext1 = dz0 - 2 * m_squish3d;
                    xsv_ext1 = xsb + 2;
                    ysv_ext1 = ysb;
                    zsv_ext1 = zsb;
                } else if ((c & 0x02) != 0) {
                    dx_ext1 = dx0 - 2 * m_squish3d;
                    dy_ext1 = dy0 - 2 - 2 * m_squish3d;
                    dz_ext1 = dz0 - 2 * m_squish3d;
                    xsv_ext1 = xsb;
                    ysv_ext1 = ysb + 2;
                    zsv_ext1 = zsb;
                } else {
                    dx_ext1 = dx0 - 2 * m_squish3d;
                    dy_ext1 = dy0 - 2 * m_squish3d;
                    dz_ext1 = dz0 - 2 - 2 * m_squish3d;
                    xsv_ext1 = xsb;
                    ysv_ext1 = ysb;
                    zsv_ext1 = zsb + 2;
                }
            } else { // Both closest points on (0,0,0) side

                // One of the two extra points is (0,0,0)
                dx_ext0 = dx0;
                dy_ext0 = dy0;
                dz_ext0 = dz0;
                xsv_ext0 = xsb;
                ysv_ext0 = ysb;
                zsv_ext0 = zsb;

                // Other extra point is based on the omitted axis.
                char c = static_cast<char>(aPoint | bPoint);
                if ((c & 0x01) == 0) {
                    dx_ext1 = dx0 + 1 - m_squish3d;
                    dy_ext1 = dy0 - 1 - m_squish3d;
                    dz_ext1 = dz0 - 1 - m_squish3d;
                    xsv_ext1 = xsb - 1;
                    ysv_ext1 = ysb + 1;
                    zsv_ext1 = zsb + 1;
                } else if ((c & 0x02) == 0) {
                    dx_ext1 = dx0 - 1 - m_squish3d;
                    dy_ext1 = dy0 + 1 - m_squish3d;
                    dz_ext1 = dz0 - 1 - m_squish3d;
                    xsv_ext1 = xsb + 1;
                    ysv_ext1 = ysb - 1;
                    zsv_ext1 = zsb + 1;
                } else {
                    dx_ext1 = dx0 - 1 - m_squish3d;
                    dy_ext1 = dy0 - 1 - m_squish3d;
                    dz_ext1 = dz0 + 1 - m_squish3d;
                    xsv_ext1 = xsb + 1;
                    ysv_ext1 = ysb + 1;
                    zsv_ext1 = zsb - 1;
                }
            }
        } else { // One point on (0,0,0) side, one point on (1,1,1) side
            char c1, c2;
            if (aIsFurtherSide) {
                c1 = aPoint;
                c2 = bPoint;
            } else {
                c1 = bPoint;
                c2 = aPoint;
            }

            // One contribution is a permutation of (1,1,-1)
            if ((c1 & 0x01) == 0) {
                dx_ext0 = dx0 + 1 - m_squish3d;
                dy_ext0 = dy0 - 1 - m_squish3d;
                dz_ext0 = dz0 - 1 - m_squish3d;
                xsv_ext0 = xsb - 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb + 1;
            } else if ((c1 & 0x02) == 0) {
                dx_ext0 = dx0 - 1 - m_squish3d;
                dy_ext0 = dy0 + 1 - m_squish3d;
                dz_ext0 = dz0 - 1 - m_squish3d;
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb - 1;
                zsv_ext0 = zsb + 1;
            } else {
                dx_ext0 = dx0 - 1 - m_squish3d;
                dy_ext0 = dy0 - 1 - m_squish3d;
                dz_ext0 = dz0 + 1 - m_squish3d;
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb - 1;
            }

            // One contribution is a permutation of (0,0,2)
            dx_ext1 = dx0 - 2 * m_squish3d;
            dy_ext1 = dy0 - 2 * m_squish3d;
            dz_ext1 = dz0 - 2 * m_squish3d;
            xsv_ext1 = xsb;
            ysv_ext1 = ysb;
            zsv_ext1 = zsb;
            if ((c2 & 0x01) != 0) {
                dx_ext1 -= 2;
                xsv_ext1 += 2;
            } else if ((c2 & 0x02) != 0) {
                dy_ext1 -= 2;
                ysv_ext1 += 2;
            } else {
                dz_ext1 -= 2;
                zsv_ext1 += 2;
            }
        }

        // Contribution (1,0,0)
        float dx1 = dx0 - 1 - m_squish3d;
        float dy1 = dy0 - 0 - m_squish3d;
        float dz1 = dz0 - 0 - m_squish3d;
        float attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate(xsb + 1, ysb + 0, zsb + 0, dx1, dy1, dz1);
        }

        // Contribution (0,1,0)
        float dx2 = dx0 - 0 - m_squish3d;
        float dy2 = dy0 - 1 - m_squish3d;
        float dz2 = dz1;
        float attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate(xsb + 0, ysb + 1, zsb + 0, dx2, dy2, dz2);
        }

        // Contribution (0,0,1)
        float dx3 = dx2;
        float dy3 = dy1;
        float dz3 = dz0 - 1 - m_squish3d;
        float attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate(xsb + 0, ysb + 0, zsb + 1, dx3, dy3, dz3);
        }

        // Contribution (1,1,0)
        float dx4 = dx0 - 1 - 2 * m_squish3d;
        float dy4 = dy0 - 1 - 2 * m_squish3d;
        float dz4 = dz0 - 0 - 2 * m_squish3d;
        float attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate(xsb + 1, ysb + 1, zsb + 0, dx4, dy4, dz4);
        }

        // Contribution (1,0,1)
        float dx5 = dx4;
        float dy5 = dy0 - 0 - 2 * m_squish3d;
        float dz5 = dz0 - 1 - 2 * m_squish3d;
        float attn5 = 2 - dx5 * dx5 - dy5 * dy5 - dz5 * dz5;
        if (attn5 > 0) {
            attn5 *= attn5;
            value += attn5 * attn5 * extrapolate(xsb + 1, ysb + 0, zsb + 1, dx5, dy5, dz5);
        }

        // Contribution (0,1,1)
        float dx6 = dx0 - 0 - 2 * m_squish3d;
        float dy6 = dy4;
        float dz6 = dz5;
        float attn6 = 2 - dx6 * dx6 - dy6 * dy6 - dz6 * dz6;
        if (attn6 > 0) {
            attn6 *= attn6;
            value += attn6 * attn6 * extrapolate(xsb + 0, ysb + 1, zsb + 1, dx6, dy6, dz6);
        }
    }

    // First extra vertex
    float attn_ext0 = 2 - dx_ext0 * dx_ext0 - dy_ext0 * dy_ext0 - dz_ext0 * dz_ext0;
    if (attn_ext0 > 0) {
        attn_ext0 *= attn_ext0;
        value += attn_ext0 * attn_ext0
            * extrapolate(xsv_ext0, ysv_ext0, zsv_ext0, dx_ext0, dy_ext0, dz_ext0);
    }

    // Second extra vertex
    float attn_ext1 = 2 - dx_ext1 * dx_ext1 - dy_ext1 * dy_ext1 - dz_ext1 * dz_ext1;
    if (attn_ext1 > 0) {
        attn_ext1 *= attn_ext1;
        value += attn_ext1 * attn_ext1
            * extrapolate(xsv_ext1, ysv_ext1, zsv_ext1, dx_ext1, dy_ext1, dz_ext1);
    }

    return value / m_norm3d;
}

float OpenSimplexNoise3D::extrapolate(int xsb, int ysb, int zsb, float dx, float dy, float dz) const
{
    int index = m_permGradIndex3d[(m_perm[(m_perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF];
    return m_gradients3d[index] * dx + m_gradients3d[index + 1] * dy
        + m_gradients3d[index + 2] * dz;
}

} // namespace jt
