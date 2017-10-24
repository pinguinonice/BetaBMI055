Bibliothek fuer 
- InvenSense ICM20601
- Maxim MAX17048

DS und RM:
ICM-20601 Datasheet - DS-000191, Revision: 1.0
http://www.invensense.com/wp-content/uploads/2015/12/DS-000191-ICM-20601-v1.0.pdf

http://datasheets.maximintegrated.com/en/ds/MAX17048-MAX17049.pdf


Aufzeichne der ueber WiFi uebertragenen Daten:

nc -l -k -p 6666 | ts "%H %M %.S " | tee  sensor_data.txt
