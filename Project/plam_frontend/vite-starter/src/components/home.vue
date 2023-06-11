<script setup lang="ts">
import { ref } from "vue";
import {Notify} from '@nutui/nutui';
import axios from "axios";
// defineProps<{ msg: string }>();
const hasresult=ref(false);
const haserr=ref(false);
const result=ref("");
const errlog=ref("");
let myimage="";

const hand_recognize=async()=>{
  myimage="";
  hasresult.value=false;
  haserr.value=false;
  document.addEventListener("deviceready", onDeviceReady, false);
    function onDeviceReady() {
        Notify.primary(navigator.camera);
    }
    try {
        // 确保 Cordova 已经加载
        if (window.cordova) {
            const options = {
                quality: 50,
                destinationType: Camera.DestinationType.DATA_URL,
                sourceType: Camera.PictureSourceType.CAMERA,
                encodingType: Camera.EncodingType.JPEG,
                mediaType: Camera.MediaType.PICTURE
            };

            // Wrap getPicture in a Promise so we can use async/await
            const getPicture = (options) => new Promise((resolve, reject) => {
                navigator.camera.getPicture(resolve, reject, options);
            });

            // Use await to wait for the picture
            const imageData = await getPicture(options);
            myimage = 'data:image/jpeg;base64,'+imageData;
            //console.log(myimage);
            let config={
              url:'/recognize',
              method:'post',
              headers:{
                'Content-Type':'multipart/form-data'
              },
              data:{
                  file:myimage
              }
            };
            axios(config).then((res)=>{
              hasresult.value=true;
              result.value=res.data['result'];
            }).catch((err)=>{
              haserr.value=true;
              hasresult.value=false;
              errlog.value=err;
              Notify.danger(err);
            });
        } else {
            console.log('Cordova is not loaded');
        }
    } catch (error) {
        Notify.primary('Error opening camera', error);
    }
}
</script>

<template>
  <div class="imgcontainer">
    <img src="../assets/logo.png" alt="Avatar" class="centered-image">
  </div>

  <div class="funitem">
    <func msg="HandRecognize" background-color="#e23c13" text-color="white" @click="hand_recognize"></func>
  </div>
  <div v-if="hasresult" class="uinfo">
    <img :src="myimage" alt="Avatar" class="centered-image">
  <p>UserInfo</p>
  <p>{{result}}</p>
  </div>
  <van-popup v-model:show="haserr" round position="bottom" :style="{height:'30%'}">
  {{ errlog  }}
  </van-popup>
</template>

<style scoped>
.ep-button {
  margin: 4px;
}
.ep-button + .ep-button {
  margin-left: 0;
  margin: 4px;
}
.funitem{
  display: flex;
  justify-content: center;
  align-items: center;
}
.imgcontainer {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 250px; /* 设置容器高度为视窗高度，使得图片可以在垂直方向上居中 */
}

.centered-image {
  height: 200px; /* 设置图片高度 */
  object-fit: contain; /* 保持图片比例 */
}
</style>
