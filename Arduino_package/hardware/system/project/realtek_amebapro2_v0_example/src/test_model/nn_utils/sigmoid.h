#ifndef __SIGMOID_H__
#define __SIGMOID_H__

float sigmoid_alt1(float x);
float sigmoid_alt2(float x);
float sigmoid_alt3(float x);

#define sigmoid(x) sigmoid_alt3(x)

float inv_sigmoid(float x);

#endif /* __SIGMOID_H__ */