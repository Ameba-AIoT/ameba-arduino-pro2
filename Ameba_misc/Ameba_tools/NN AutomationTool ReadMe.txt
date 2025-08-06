Instructions on how to change the parameters in nn_model.json file when more NN models are to be added in.
- No need to regenerate all the tool exe files.
- Edit nn_model.json accordingly when new model is added.
- nn_model.json can be found in Arduino15\packages\realtek\tools\ameba_pro2_tools\{tools version}\misc.

NNTasks: Total number of NN tasks (e.g. Object Detection, Face Detection, Face Recognition ,etc)
modelCount: Total numbers of model type (YOLO v3/v4/v7 count as 1 type).
ModelSelectParamsCount: Total number of parameters in ModelSelect function. Refer to NNModelSelection.h.
nn_task: List out all the available NN Tasks.
error_handler: To check if the NN task input by the user is valid. Use keywords to verify.
header: using keywords to retrieve header file (e.g. NNObjectDetection.h) from ino file.
modelkeyword: using keywords to verify that the model input by user is valid according to the assigned NN Task.
model_mappings: map the input from ModelSelect function to model name used in amebapro2_fwfs_nn_models.json to update amebapro2_fwfs_nn_models.json.
nb_file_mapping: map model keywords (from amebapro2_fwfs_nn_models.json) to their respective file names.
