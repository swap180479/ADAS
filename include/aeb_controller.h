#ifndef AEB_CONTROLLER_H
#define AEB_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AEB_OK = 0,
    AEB_INVALID_INPUT = 1
} AebStatus;

typedef struct {
    int brake_request;
    double ttc_s;
} AebDecision;

/* Educational example: NOT suitable for real vehicle control. */
AebStatus aeb_evaluate(double distance_m,
                       double closing_speed_mps,
                       AebDecision *out);

#ifdef __cplusplus
}
#endif

#endif
