1. Copy ทุกไฟล์ในโฟลเดอร์ Code เอาไปไว้ในโฟลเดอร์ที่มี code เก่าอยู่
2. Copy ทุกไฟล์ในโฟลเดอร์ Resource ไปวางในโฟลเดอร์ Resource เก่า
3. เปิดโปรเจคขึ้นมาตรง Solution Explorer ด้านขวามือคลิกขวาที๋โฟลเดอร์ไหนก็ได้แล้วเลือก Add->Existing Item แล้วเพิ่ม ImageObject.h กับ ImageObject.cpp เข้ามาในโปรเจค
4. ตรง Solution Explorer คลิกขวาที่โปรเจคเลือก Properties ไปที่ Linker->Input->Additional Dependencies เพิ่มคำว่า SDL2_image.lib เข้าไป