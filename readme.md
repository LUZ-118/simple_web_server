執行環境：ubuntu 20.04
程式語言：C++

使用方法：
### C++版本
執行server.cpp，並在瀏覽器輸入 http://IP:3400/File_Name 即可
IP-實體IP （需開防火牆）或者 127.0.0.1（本機執行），區域網路應該可以用虛擬IP
File_Name-有兩個檔案，要跟server.cpp放同一個資料夾，為Page1.html & Page2.html。

### Python版本
執行server.py後，在離瀏覽器輸入http://IP:12345/PageX.html(X可以是1or2，其他的話會404error)，
IP的話如果是在檔案所在的電腦執行可以輸入127.0.0.1，如果是在別台電腦連過去則輸入檔案所在電腦的實體IP(都連同一網路的話可以輸入虛擬IP?)，
檔案需要放在跟python檔同一目錄上。
