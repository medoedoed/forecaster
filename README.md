## Консольное приложение для отображения прогноза погоды

### Источники данных

- [Open-Meteo](https://open-meteo.com/en/docs#latitude=59.94&longitude=30.31&hourly=temperature_2m&forecast_days=16) – для получения прогноза
- [Api-Ninjas](https://api-ninjas.com/api/city) – для определения координат по названию города

### Функционал

- Отображение прогноза погоды на несколько дней вперед (значение по умолчанию задается в конфигурации)
- Обновление прогноза с заданной частотой (устанавливается в конфигурации)
- Переключение между городами с помощью клавиш "n" и "p"
- Завершение работы программы по нажатию клавиши "Esc"
- Изменение количества дней прогноза клавишами "+" и "-"

Список городов, частота обновления и количество дней прогноза определены в конфигурационном файле (в формате JSON)
