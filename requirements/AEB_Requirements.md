# AEB sample requirements

Version: 1.0 — educational demonstration only.

## Interface
`aeb_evaluate(double distance_m, double closing_speed_mps, AebDecision *out)` returns an `AebStatus`. `out` must point to writable memory. On valid inputs, `out->brake_request` is 0 or 1 and `out->ttc_s` is the calculated TTC, or `INFINITY` when not closing.

## Requirements
- **AEB-REQ-001 (input validation):** Reject null output pointers, negative distance, negative closing speed, and non-finite distance or closing speed with `AEB_INVALID_INPUT`.
- **AEB-REQ-002 (safe output on invalid numeric input):** If `out` is non-null, initialize `brake_request=0` and `ttc_s=INFINITY` before validating numeric inputs.
- **AEB-REQ-003 (not closing):** For `closing_speed_mps == 0`, return `AEB_OK`, `brake_request=0`, and `ttc_s=INFINITY`.
- **AEB-REQ-004 (TTC):** For valid positive closing speed, compute `ttc_s = distance_m / closing_speed_mps`.
- **AEB-REQ-005 (threshold):** For valid positive closing speed, request braking (`brake_request=1`) when `ttc_s <= 2.0`; otherwise set `brake_request=0`.
- **AEB-REQ-006 (zero distance):** With valid positive closing speed and zero distance, return `AEB_OK`, TTC zero, and brake request 1.

## Acceptance vectors

| Test ID | Requirement(s) | distance_m | closing_speed_mps | Expected status | Brake | TTC |
| --- | --- | ---: | ---: | --- | ---: | ---: |
| TC-001 | 003 | 20 | 0 | AEB_OK | 0 | infinity |
| TC-002 | 004,005 | 30 | 10 | AEB_OK | 0 | 3 |
| TC-003 | 004,005 | 20 | 10 | AEB_OK | 1 | 2 |
| TC-004 | 004,005 | 10 | 10 | AEB_OK | 1 | 1 |
| TC-005 | 006 | 0 | 10 | AEB_OK | 1 | 0 |
| TC-006 | 001,002 | -1 | 10 | AEB_INVALID_INPUT | 0 | infinity |
| TC-007 | 001,002 | 10 | -1 | AEB_INVALID_INPUT | 0 | infinity |
| TC-008 | 001,002 | NaN | 10 | AEB_INVALID_INPUT | 0 | infinity |
| TC-009 | 001 | 10 | 10, out=null | AEB_INVALID_INPUT | N/A | N/A |

Traceability is limited to these educational sample requirements and the source implementation. No ASPICE compliance or safety certification is claimed.
