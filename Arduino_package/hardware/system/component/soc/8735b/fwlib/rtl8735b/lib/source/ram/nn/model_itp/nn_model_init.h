#ifndef NNMODEL_INIT_H_
#define NNMODEL_INIT_H_

int nn_model_download(unsigned char id);
int nn_model_info_set(unsigned char id, struct MODEL_INFO_S *model_info);
int nn_model_interpreted(unsigned char id, struct MODEL_INFO_S *model_info);

#endif //NNMODEL_INIT_H_

