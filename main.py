import serial
from ultralytics import YOLO
# Mở kết nối Serial tới cổng COM3 với tốc độ baud rate 115200
ser = serial.Serial('COM3', 115200, timeout=1)
ser.flush()
# Tải mô hình
model = YOLO("best.pt") #'best.pt' là đường dẫn đúng tới mô hình
# Dự đoán sử dụng generator cho các luồng dữ liệu dài hoặc nguồn dữ liệu lớn
results_generator = model.predict(source="0", show=True, stream=True)
# Lặp qua generator của các đối tượng kết quả
for results in results_generator:
# Kiểm tra xem có phát hiện nào không bằng cách kiểm tra độ dài của thuộc
tính boxes
for r in results:
for c in r.boxes.cls:
class_name = model.names[int(c)]
print(class_name) # In tên lớp
# Gửi tên lớp đến Arduino
ser.write((class_name + '\n').encode('utf-8'))
# Đóng kết nối Serial khi hoàn tất
ser.close()