# handmade_BasketballArcade

一.	系統功能與原理說明:
   程式開始執行時遊戲開始倒數計時，LED顯示器上會顯示剩餘時間。用手指按動開關把籃球彈入籃框裡面,籃框裡面有架設紅外線感應器,會感測籃球通過,並計算分數,並用LED區段顯示器(記分板)顯示分數,再用喇叭放出投籃音效等等,籃框是經由馬達帶動圓盤便可以左右移動。
   
二.	系統使用環境及對象:
* 對象:pic18F4520晶片
* 環境:MPLAB xc8

三.	系統完整流程圖或架構圖:
![](https://github.com/f74066357/handmade_BasketballArcade/blob/master/src/process.png)

四.  系統開發工具、材料、及技術:

* 材料:pic18F4520晶片x2、紅外線感測器、蜂鳴器、伺服馬達 
* 技術:
    1. 使用pwm控制馬達轉動帶動厚紙板圓盤使籃框左右移動
    2. 使用interrupt 控制紅外線感測器當感測到物體時就觸發interrupt並讓七段顯示器加分
    3. 使用多工和視覺暫留控制七段顯示器

五.	遇到的困難:
    本來想要讓馬達和七段顯示器都是用同一個pic控制,但是發現這兩個的頻率沒辦法同一個,若是降低頻率,七段顯示器就會因為頻率過低而沒辦法達到視覺暫留的效果,若是提高頻率,就蠻辦法符合伺服馬達的頻率

六.實際圖片
* 馬達帶動的圓盤 ![](https://github.com/f74066357/handmade_BasketballArcade/blob/master/src/1.jpg)
* 籃球發射器    ![](https://github.com/f74066357/handmade_BasketballArcade/blob/master/src/2.jpg)
* 籃機整體架構 ![](https://github.com/f74066357/handmade_BasketballArcade/blob/master/src/3.jpg)
