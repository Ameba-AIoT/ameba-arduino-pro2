/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_LOG_TRANSPORT_H
#define AMEBA_LOG_TRANSPORT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Logging transports, bit mask to select features. Function returns selection.
 */
#define LOGGER_DEFAULT 0x00
#define LOGGER_LOGD    0x01
#define LOGGER_NULL    0x02 /* Does not release resources of other selections */
#define LOGGER_STDOUT  0x08 /* logs sent to stdout */

/* Both return the selected transport flag mask, or negative errno */
int amebaSetLogTransport(int transport);
int amebaGetLogTransport();

#ifdef __cplusplus
}
#endif

#endif /* AMEBA_LOG_TRANSPORT_H */
