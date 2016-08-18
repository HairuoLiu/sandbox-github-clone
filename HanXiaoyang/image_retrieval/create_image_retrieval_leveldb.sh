#!/usr/bin/env sh
# 将图片转存到leveldb中
#设定训练和测试数据list存储文件目录，编译好的caffe可执行文件目录
EXAMPLE=/home/work/hangxiaoyang/image_retrieval/caffe/examples
DATA=/home/work/hangxiaoyang/image_retrieval/caffe/dataset
TOOLS=/home/work/hangxiaoyang/image_retrieval/caffe/build/tools

#设定训练和测试图片集所在根目录
TRAIN_DATA_ROOT=/home/work/hanxiaoyang/pic/
VAL_DATA_ROOT=/home/work/hanxiaoyang/pic/

# 设定RESIZE=true将scale图片至256x256.如果图片已经做过resize，设定为false.
RESIZE=true
if $RESIZE; then
  RESIZE_HEIGHT=256
  RESIZE_WIDTH=256
else
  RESIZE_HEIGHT=0
  RESIZE_WIDTH=0
fi

if [ ! -d "$TRAIN_DATA_ROOT" ]; then
  echo "Error: TRAIN_DATA_ROOT is not a path to a directory: $TRAIN_DATA_ROOT"
  echo "Set the TRAIN_DATA_ROOT variable in create_imagenet.sh to the path" \
       "where the ImageNet training data is stored."
  exit 1
fi

if [ ! -d "$VAL_DATA_ROOT" ]; then
  echo "Error: VAL_DATA_ROOT is not a path to a directory: $VAL_DATA_ROOT"
  echo "Set the VAL_DATA_ROOT variable in create_imagenet.sh to the path" \
       "where the ImageNet validation data is stored."
  exit 1
fi

echo "Creating train leveldb..."

GLOG_logtostderr=1 $TOOLS/convert_imageset \
    --resize_height=$RESIZE_HEIGHT \
    --resize_width=$RESIZE_WIDTH \
    --shuffle \
    --backend="leveldb" \
    $TRAIN_DATA_ROOT \
    $DATA/train.txt \
    $EXAMPLE/image_retrieval_train_leveldb

echo "Creating val leveldb..."

GLOG_logtostderr=1 $TOOLS/convert_imageset \
    --resize_height=$RESIZE_HEIGHT \
    --resize_width=$RESIZE_WIDTH \
    --shuffle \
    --backend="leveldb" \
    $VAL_DATA_ROOT \
    $DATA/val.txt \
    $EXAMPLE/image_retrieval_val_leveldb

echo "Done."
