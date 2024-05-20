#ifndef __CLASSIFICATIONCLASSLIST_H__
#define __CLASSIFICATIONCLASSLIST_H__

struct ClassificationDetectionItem {
    uint8_t index;
    const char* imgclassName;
    uint8_t filter;
};

// List of objects the pre-trained model is capable of recognizing
// Index number is fixed and hard-coded from training
// Set the filter value to 0 to ignore any recognized objects
ClassificationDetectionItem imgclassItemList[6] = {
    {0, "cardboard", 1},
    {1, "glass",     1},
    {2, "metal",     1},
    {3, "paper",     1},
    {4, "plastic",   1},
    {5, "trash",     1}
};

#endif
