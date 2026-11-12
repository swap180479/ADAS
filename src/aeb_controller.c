#include "aeb_controller.h"

#include <math.h>

#define AEB_TTC_THRESHOLD_S 2.0

AebStatus aeb_evaluate(double distance_m,
                       double closing_speed_mps,
                       AebDecision *out)
{
    if (out == NULL) {
        return AEB_INVALID_INPUT;
    }

    out->brake_request = 0;
    out->ttc_s = INFINITY;

    if (!isfinite(distance_m) || !isfinite(closing_speed_mps) ||
        distance_m < 0.0 || closing_speed_mps < 0.0) {
        return AEB_INVALID_INPUT;
    }

    if (closing_speed_mps == 0.0) {
        return AEB_OK;
    }

    out->ttc_s = distance_m / closing_speed_mps;
    if (out->ttc_s <= AEB_TTC_THRESHOLD_S) {
        out->brake_request = 1;
    }

    return AEB_OK;
}
