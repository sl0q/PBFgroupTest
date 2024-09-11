# Тестовое задание для ООО PFB group

Проект содержит код для сервеной и клиентской частей приложения для платформы Linux. 

## Сборка и запуск
### VSCode
Для Visual Studio Code настроенf автоматическая сборка для Linux с использованием CMake. Для запуска нужно выбрать соответстующую задачу в меню запуска отдельно для клиента и сервера.

### Вручную
Для сборки вручную нужно последовательно выполнить следующие команды:
```
mkdir build
cd build
cmake ../.
cmake --build .
```
В результате, в папке `build` должно появится два исполнительных файла `server` и `client`.
