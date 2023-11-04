# Internet of Trees

## Introduction
With global warming and human activity, the occurence of wildfires are gradually increasing. 
In order to provide early warning and detect the fire as soon as possible, this project, Internet of Trees is created.
The project is to build a network of sensors that can detect the fire and send the information to the server.
The server will then send the information to the user's phone and the user can take action to prevent the fire from spreading.
The user's phone also forwards the current data to a machine learning model to predict the possibility of fire based on the current situation.

## The Things
The physical things are packed into a single box. The box contains solar panels for power, batteries, an esp8266/Arduino for processing, and finally enough sensors to detect the following:
Early warning:
    - Temperature
    - Humidity
    - Soil moisture
Fire:
    - Flames
    - Smoke

## The Server
The server is a simple firebase database hosted on google that stores the data from the things.

## The App
The app is an android app that displays the data from the server and sends notifications to the user when the fire is detected.

## The model 
The model is built using Keras with python. The model is available and running at *https://lorax.azurewebsites.net/* for open source use as well.
Sending a json **`PUT`** request with the following to the endpoint **`/predict`**:

```json

        {
        "region": "region",
        "date": "yyyy-mm-dd",", 
        "temp": 0.0,
        "humidity": 0.0
        }

```

<br/>

Here's an example:
```json
    {
    "region": "London",
    "date": "2023-10-23", 
    "temp": 20,
    "humidity": 80
    }
```
The model best works for countries with a tropical climate.