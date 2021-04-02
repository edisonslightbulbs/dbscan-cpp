#ifndef PROPOSAL_H
#define PROPOSAL_H

#include "point.h"
#include <Eigen/Dense>
#include <vector>

namespace grow {

/**
 * grow
 *   Grows proposal of tabletop interaction context.
 *
 * @param solution
 *   Computed SVD (singular value decomposition).
 *
 * @retval
 *    Coarse segment/proposal region of tabletop interaction context.
 */
std::vector<Point> propose(
    const std::pair<Eigen::JacobiSVD<Eigen::MatrixXd>, Eigen::MatrixXd>&
        solution,
    std::vector<Point>& points);
}

#endif /* PROPOSAL_H */