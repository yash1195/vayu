'use strict';
const Alexa = require('alexa-sdk');
const request = require('request');

const APP_ID = undefined;

const HELP_REPROMPT = 'What can I help you with?';
const STOP_MESSAGE = 'Goodbye!';
const FAN_POWER_EVENT_VERBAL_RESPONSE = 'On it!';

// Vayu Control Message Codes
const FAN_POWER_CM = 5;
const FAN_SPEED_CM = 6;
const FAN_SWING_CM = 7;

const ADAFRUIT_URL = "https://io.adafruit.com/api/v2/yashchoukse/groups/vayunetwork/feeds/fan-control/data";

// secret
const ADAFRUIT_SECRET = '######';

const handlers = {
    'AMAZON.HelpIntent': function () {
        const speechOutput = HELP_MESSAGE;
        const reprompt = HELP_REPROMPT;

        this.response.speak(speechOutput).listen(reprompt);
        this.emit(':responseReady');
    },
    'AMAZON.CancelIntent': function () {
        this.response.speak(STOP_MESSAGE);
        this.emit(':responseReady');
    },
    'AMAZON.StopIntent': function () {
        this.response.speak(STOP_MESSAGE);
        this.emit(':responseReady');
    },
    'fan_power': function () {

		// send control message to Adafruit
        let url = ADAFRUIT_URL;
        
        let options = {
            url: url,
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
                'X-AIO-Key': ADAFRUIT_SECRET
            },
            form: {
                'value': FAN_POWER_CM
            }
		};
		
		let context = this;
        
        request.post(options, function(err, resp, body) {
            
            if (err) {
                context.response.speak(CONTROL_MESSAGE_TRANSMISSION_FAILED);
            } else {
				console.log(resp);
				console.log(body);
                context.response.speak(FAN_POWER_EVENT_VERBAL_RESPONSE);    
            }
            context.emit(':responseReady');
        });
        
    },
    'fan_speed': function () {

		// send control message to Adafruit
        let url = ADAFRUIT_URL;
        
        let options = {
            url: url,
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
                'X-AIO-Key': ADAFRUIT_SECRET
            },
            form: {
                'value': FAN_SPEED_CM
            }
		};
		
		let context = this;
        
        request.post(options, function(err, resp, body) {
            
            if (err) {
                context.response.speak(CONTROL_MESSAGE_TRANSMISSION_FAILED);
            } else {
				console.log(resp);
				console.log(body);
                context.response.speak(FAN_POWER_EVENT_VERBAL_RESPONSE);    
            }
            context.emit(':responseReady');
        });
        
    },
    'fan_swing': function () {

		// send control message to Adafruit
        let url = ADAFRUIT_URL;
        
        let options = {
            url: url,
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
                'X-AIO-Key': ADAFRUIT_SECRET
            },
            form: {
                'value': FAN_SWING_CM
            }
		};
		
		let context = this;
        
        request.post(options, function(err, resp, body) {
            
            if (err) {
                context.response.speak(CONTROL_MESSAGE_TRANSMISSION_FAILED);
            } else {
				console.log(resp);
				console.log(body);
                context.response.speak(FAN_POWER_EVENT_VERBAL_RESPONSE);    
            }
            context.emit(':responseReady');
        });
        
    }
};

exports.handler = function (event, context, callback) {
    
    const alexa = Alexa.handler(event, context, callback);
    alexa.APP_ID = APP_ID;
    alexa.registerHandlers(handlers);
    alexa.execute();
};
