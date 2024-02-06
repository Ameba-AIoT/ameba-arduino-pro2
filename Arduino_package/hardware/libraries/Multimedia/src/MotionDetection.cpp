#include <Arduino.h>
#include "MotionDetection.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "md_drv.h"
#include "md_api.h"
#include "module_md.h"
#include "module_eip.h"

#ifdef __cplusplus
}
#endif

std::vector<MotionDetectionResult> MotionDetection::md_result_vector;
void (*MotionDetection::MD_user_CB)(std::vector<MotionDetectionResult>);

MotionDetection::MotionDetection(uint8_t row, uint8_t col)
{
    md_eip_param.image_width = 0;
    md_eip_param.image_height = 0;
    md_eip_param.eip_row = 0;
    md_eip_param.eip_col = 0;
    configResolution(row, col);
}

MotionDetection::~MotionDetection(void)
{
    end();
}

void MotionDetection::configResolution(uint8_t row, uint8_t col)
{
    if (row > MD_MAX_ROW) {
        row = MD_MAX_ROW;
    }
    if (col > MD_MAX_COL) {
        col = MD_MAX_COL;
    }
    if (row == 0) {
        row = 1;
    }
    if (col == 0) {
        col = 1;
    }

    md_eip_param.eip_row = row;
    md_eip_param.eip_col = col;
}

void MotionDetection::configVideo(VideoSetting& config)
{
    md_eip_param.image_width = config._w;
    md_eip_param.image_height = config._h;
}

void MotionDetection::begin(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = MDInit();
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] MD init failed\n");
        return;
    }

    setMDParams(_p_mmf_context, &md_eip_param);
    setMDDisppost(_p_mmf_context, MDResultCallback);
    if (trigCount) {
        setMDTrigBlock(_p_mmf_context, trigCount);
        mm_module_ctrl(_p_mmf_context, CMD_EIP_SET_MD_OUTPUT, 1);
        mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 1);
        mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
    }
    MDBegin(_p_mmf_context, 1);
    setMDStatus(_p_mmf_context);
}

void MotionDetection::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    setMDDisppost(_p_mmf_context, NULL);
    if (MDDeinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] MD deinit failed\n");
    }
}

void MotionDetection::setTriggerBlockCount(uint16_t count)
{
    trigCount = count;
    if (_p_mmf_context == NULL) {
        return;
    }
    setMDTrigBlock(_p_mmf_context, count);
}

void MotionDetection::setDetectionMask(char* mask)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    setMDMask(_p_mmf_context, mask);
}

void MotionDetection::setResultCallback(void (*md_callback)(std::vector<MotionDetectionResult>))
{
    MD_user_CB = md_callback;
}

uint16_t MotionDetection::getResultCount(void)
{
    uint16_t md_res_count = md_result_vector.size();

    if (md_res_count >= 5) {
        md_res_count = 4;
    }
    return md_res_count;
}

MotionDetectionResult MotionDetection::getResult(uint16_t index)
{
    if (index >= md_result_vector.size()) {
        return MotionDetectionResult();
    }
    return md_result_vector[index];
}

std::vector<MotionDetectionResult> MotionDetection::getResult(void)
{
    return md_result_vector;
}

uint8_t MotionDetection::rows(void)
{
    return md_eip_param.eip_row;
}

uint8_t MotionDetection::cols(void)
{
    return md_eip_param.eip_col;
}

void MotionDetection::MDResultCallback(md_result_t* result)
{
    if (result == NULL) {
        return;
    }
    md_result_vector.clear();
    md_result_vector.resize((size_t)result->motion_cnt);

    for (int i = 0; i < result->motion_cnt; i++) {
        memcpy(&(md_result_vector[i].md_position), &(result->md_pos[i]), sizeof(md_pos_t));
    }

    if (MD_user_CB != NULL) {
        MD_user_CB(md_result_vector);
    }
}

float MotionDetectionResult::xMin(void)
{
    return md_position.xmin;
}

float MotionDetectionResult::xMax(void)
{
    return md_position.xmax;
}

float MotionDetectionResult::yMin(void)
{
    return md_position.ymin;
}

float MotionDetectionResult::yMax(void)
{
    return md_position.ymax;
}

// Function not used currently, require raw MD result to use these functions
#if 0
uint16_t MotionDetectionPostProcess::labelAdjacentRegions(char* mdResult, uint8_t rows, uint8_t cols) {
    regionCount = 0;
    memset(regionGroup, 0, sizeof(regionGroup));
    groupCount = 0;
    memset(groupMap, 0, sizeof(groupMap));
    uint8_t motion_present = 0;
    uint8_t* map = (uint8_t*)mdResult;

    // First pass
    for (uint8_t r = 0; r < rows; r++) {
        for (uint8_t c = 0; c < cols; c++) {
            if (map[(r) * cols + (c)] != 0) {
                motion_present = 1;
                // get left and top neighbours while checking for bounds
                uint8_t northw = 0, north = 0, northe = 0, west = 0;
                if ((r > 0) && (c > 0)) {
                    northw = map[(r-1) * cols + (c-1)];
                }
                if (r > 0) {
                    north = map[(r-1) * cols + (c)];
                }
                if ((r > 0) && (c < (cols-1))) {
                    northe = map[(r-1) * cols + (c+1)];
                }
                if (c > 0) {
                    west = map[(r) * cols + (c-1)];
                }

                map[(r) * cols + (c)] = regionCount + 1; // assign preliminary region
                if (!northw && !north && !northe && !west) {    // No neighbours, assign as new region
                    regionCount++;
                    regionGroup[regionCount] = regionCount;
                } else if (northw && !north && !northe && !west) {  // single neighbour, assign same region
                    map[(r) * cols + (c)] = map[(r-1) * cols + (c-1)];
                } else if (!northw && north && !northe && !west) {  // single neighbour, assign same region
                    map[(r) * cols + (c)] = map[(r-1) * cols + (c)];
                } else if (!northw && !north && northe && !west) {  // single neighbour, assign same region
                    map[(r) * cols + (c)] = map[(r-1) * cols + (c+1)];
                } else if (!northw && !north && !northe && west) {  // single neighbour, assign same region
                    map[(r) * cols + (c)] = map[(r) * cols + (c-1)];
                } else {                                            // multiple neighbours, assign smallest region number
                    if (northw && (map[(r-1) * cols + (c-1)] < map[(r) * cols + (c)])) {
                        map[(r) * cols + (c)] = map[(r-1) * cols + (c-1)];
                    }
                    if (north && (map[(r-1) * cols + (c)] < map[(r) * cols + (c)])) {
                        map[(r) * cols + (c)] = map[(r-1) * cols + (c)];
                    }
                    if (northe && (map[(r-1) * cols + (c+1)] < map[(r) * cols + (c)])) {
                        map[(r) * cols + (c)] = map[(r-1) * cols + (c+1)];
                    }
                    if (west && (map[(r) * cols + (c-1)] < map[(r) * cols + (c)])) {
                        map[(r) * cols + (c)] = map[(r) * cols + (c-1)];
                    }
                    
                    // group adjacent regions together
                    if (northw && (regionGroup[map[(r-1) * cols + (c-1)]] > regionGroup[map[(r) * cols + (c)]])) {
                        regionGroup[map[(r-1) * cols + (c-1)]] = regionGroup[map[(r) * cols + (c)]];
                    }
                    if (north && (regionGroup[map[(r-1) * cols + (c)]] > regionGroup[map[(r) * cols + (c)]])) {
                        regionGroup[map[(r-1) * cols + (c)]] = regionGroup[map[(r) * cols + (c)]];
                    }
                    if (northe && (regionGroup[map[(r-1) * cols + (c+1)]] > regionGroup[map[(r) * cols + (c)]])) {
                        regionGroup[map[(r-1) * cols + (c+1)]] = regionGroup[map[(r) * cols + (c)]];
                    }
                    if (west && (regionGroup[map[(r) * cols + (c-1)]] > regionGroup[map[(r) * cols + (c)]])) {
                        regionGroup[map[(r) * cols + (c-1)]] = regionGroup[map[(r) * cols + (c)]];
                    }
                }

            }
        }
    }

    // No motion detected, stop processing
    if (motion_present == 0) {
        region_vector.clear();
        return 0;
    }

    // Convert region group numbers to be continuous starting from 1
    for (uint16_t i = 0; i < (regionCount+1); i++) {
        groupMap[regionGroup[i]] = 1;
    }
    groupMap[0] = 0;
    for (uint16_t i = 1; i < MDMAXREGIONS; i++) {
        if (groupMap[i]) {
            groupMap[i] = ++groupCount;
        }
        if (groupCount > regionCount) {
            break;
        }
    }
    groupCount++;   // one additional group of all regions
    MotionDetectionRegion newRegion;
    newRegion.rows = rows;
    newRegion.cols = cols;
    region_vector.clear();
    region_vector.resize(groupCount, newRegion);

    // Second pass
    for (uint8_t r = 0; r < rows; r++) {
        for (uint8_t c = 0; c < cols; c++) {
            if (map[(r) * cols + (c)] != 0) {
                // change region group numbers to new numbering
                map[(r) * cols + (c)] = groupMap[regionGroup[map[(r) * cols + (c)]]];
                uint16_t regionNum = map[(r) * cols + (c)];

                // check max boundary of all regions
                if (c < region_vector[0].xmin) {
                    region_vector[0].xmin = c;
                }
                if (c > region_vector[0].xmax) {
                    region_vector[0].xmax = c;
                }
                if (r < region_vector[0].ymin) {
                    region_vector[0].ymin = r;
                }
                if (r > region_vector[0].ymax) {
                    region_vector[0].ymax = r;
                }

                // check max boundary of current region
                if (c < region_vector[regionNum].xmin) {
                    region_vector[regionNum].xmin = c;
                }
                if (c > region_vector[regionNum].xmax) {
                    region_vector[regionNum].xmax = c;
                }
                if (r < region_vector[regionNum].ymin) {
                    region_vector[regionNum].ymin = r;
                }
                if (r > region_vector[regionNum].ymax) {
                    region_vector[regionNum].ymax = r;
                }
                region_vector[regionNum].blockCount++;
            }
        }
    }

    return (groupCount);
}

uint16_t MotionDetectionPostProcess::getRegionCount(void) {
    return region_vector.size();
}

MotionDetectionRegion MotionDetectionPostProcess::getRegion(uint16_t index) {
    if (index >= region_vector.size()) {
        return MotionDetectionRegion();
    }
    return region_vector[index];
}

std::vector<MotionDetectionRegion> MotionDetectionPostProcess::getRegion(void) {
    return region_vector;
}

uint16_t MotionDetectionRegion::size(void) {
    return blockCount;
}

float MotionDetectionRegion::xMin(void) {
    return (xmin * (1.0 / cols));
}

float MotionDetectionRegion::xMax(void) {
    return ((xmax + 1) * (1.0 / cols));
}

float MotionDetectionRegion::yMin(void) {
    return (ymin * (1.0 / rows));
}

float MotionDetectionRegion::yMax(void) {
    return ((ymax + 1) * (1.0 / rows));
}
#endif
