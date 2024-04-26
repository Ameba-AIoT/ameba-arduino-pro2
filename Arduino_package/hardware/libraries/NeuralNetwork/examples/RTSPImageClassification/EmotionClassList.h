#ifndef __EMOTIONCLASSLIST_H__
#define __EMOTIONCLASSLIST_H__

struct EmotionDetectionItem {
    uint8_t index;
    const char* imgclassName;
    uint8_t filter;
};

// List of objects the pre-trained model is capable of recognizing
// Index number is fixed and hard-coded from training
// Set the filter value to 0 to ignore any recognized objects
EmotionDetectionItem imgclassItemList[7] = {
    {0, "angry",    1},
    {1, "disgust",  1},
    {2, "fear",     1},
    {3, "happy",    1},
    {4, "neutral",  1},
    {5, "sad",      1},
    {6, "surprise", 1}
};

#endif
