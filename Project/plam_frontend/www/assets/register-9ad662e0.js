import{_ as I}from"./func-121e8e9c.js";import{d as S,r as c,a as v,c as T,b as m,e as r,w as C,f as U,F as V,o as w,g as P,t as E,p as b,h as L,N as a,i as N,_ as j}from"./index-923e9538.js";const R={},H=p=>(b("data-v-f96412aa"),p=p(),L(),p),M=H(()=>m("span",null,"Image count:",-1)),B={class:"funitem"},F={class:"funitem"},q={class:"funitem"},z={key:0},y=2,G=S({__name:"register",setup(p){const f=c([]),h=c([]),_=c(!1),g=c(""),l=c(0),u=c(0),D=async()=>{let s=y-l.value;if(s==0){a.primary("Already Done");return}document.addEventListener("deviceready",t,!1);function t(){a.primary(navigator.camera)}try{if(window.cordova){const n={quality:25,destinationType:Camera.DestinationType.DATA_URL,sourceType:Camera.PictureSourceType.CAMERA,encodingType:Camera.EncodingType.JPEG,mediaType:Camera.MediaType.PICTURE};async function i(e){return new Promise((o,d)=>{navigator.camera.getPicture(o,d,e)})}for(let e=0;e<s;e++){const o=await i(n);f.value.push("data:image/jpeg;base64,"+o),l.value++}}else R.log("Cordova is not loaded")}catch(n){a.primary("Error opening camera",n)}},k=async()=>{let s=y-u.value;if(s==0){a.primary("Already Done");return}document.addEventListener("deviceready",t,!1);function t(){a.primary(navigator.camera)}try{if(window.cordova){const n={quality:25,destinationType:Camera.DestinationType.DATA_URL,sourceType:Camera.PictureSourceType.CAMERA,encodingType:Camera.EncodingType.JPEG,mediaType:Camera.MediaType.PICTURE};async function i(e){return new Promise((o,d)=>{navigator.camera.getPicture(o,d,e)})}for(let e=0;e<s;e++){const o=await i(n);h.value.push("data:image/jpeg;base64,"+o),u.value++}}else R.log("Cordova is not loaded")}catch(n){a.primary("Error opening camera",n)}},x=()=>{if(g.value==""){a.warn("Please input username");return}if(l.value!=y||u.value!=y){a.warn("Please take enough photos");return}_.value=!0;let s={method:"post",url:"/register",headers:{"Content-Type":"application/json"},data:{username:g.value,left_images:f.value,right_images:h.value}};N(s).then(t=>{_.value=!1,t.data.code==0?a.success("Register Success"):a.danger("Register Failed"),l.value=0,u.value=0,f.value=[],h.value=[]}).catch(t=>{_.value=!1,a.danger(t)})};return(s,t)=>{const n=v("van-tag"),i=I,e=v("van-field"),o=v("van-cell-group"),d=v("nut-icon");return w(),T(V,null,[m("div",null,[M,r(n,{type:"primary",size:"large",class:"tag"},{default:C(()=>[P("LeftHand:"+E(l.value),1)]),_:1}),r(n,{type:"primary",size:"large"},{default:C(()=>[P("RightHand:"+E(u.value),1)]),_:1})]),m("div",B,[r(i,{msg:"LeftHand",onClick:D})]),m("div",F,[r(i,{msg:"RightHand",onClick:k})]),r(o,{inset:"",style:{"justify-content":"center",display:"flex"}},{default:C(()=>[r(e,{modelValue:g.value,"onUpdate:modelValue":t[0]||(t[0]=A=>g.value=A),label:"Username",placeholder:"Your Username",class:"inputbox"},null,8,["modelValue"])]),_:1}),m("div",q,[r(i,{msg:"Register","background-color":"#749938","text-color":"white",onClick:x})]),_.value?(w(),T("div",z,[r(d,{name:"loading1"})])):U("",!0)],64)}}});const K=j(G,[["__scopeId","data-v-f96412aa"]]);export{K as default};