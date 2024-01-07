# Real-Time Market Event Notification System

## Overview
This **Real-Time Market Event Notification System** is designed for traders and market enthusiasts who seek efficient market monitoring without being tethered to their screens constantly. By leveraging real-time notifications, this system alerts users to significant market events directly on their mobile devices, tablets, or computers, enabling them to focus on the market when it's most crucial.

## Key Features

- **Integration with Existing Applications**: Utilizes popular platforms to reduce development costs and maintenance needs.
- **SierraChart Real-Time Data**: Runs on SierraChart with a real-time data feed, ensuring prompt and accurate market information.
- **Customized Market Analysis**: Employs a specially developed study that analyzes live market data to detect critical trading moments and generate actionable signals.
- **Secure and Targeted Notifications via Slack**: Once a market event is detected, the system communicates with the configured Slack API to deliver these signals securely. Notifications are sent to the appropriate channels, ensuring they reach the right audience.

## Technical Details

- **Development**: The system is crafted in C++, tailored to SierraChart's robust environment.
- **Slack API Integration**: Uses cURL for seamless and reliable communication with the Slack API, ensuring prompt delivery of notifications.

## Benefits

- **Stay Informed on the Go**: Receive immediate alerts about significant market movements, allowing for timely decisions.
- **Minimize Screen Time**: Frees you from the need to continuously watch market fluctuations, offering flexibility and efficiency.
- **Customized Alerts**: Tailored notifications based on sophisticated market analysis, ensuring relevance and accuracy.

## How to use

- *Creat a Webhook in you Slack API*: In the Slack API of your apps (https://api.slack.com) creat a webhook. It should point to a notification channel you created. Save the URL.
- *Compile Custom study*: Open the project in Visual Studio and compile it. Optional : change in ECIMACross2Slack/ECIMACross2Slack.h file Slack URL constant (ECI_MACROSS_TO_SLACK_APIWEBHOOKURL).
- *Creat a chartbook in SierraChart*: A chartbook is provided in CHT folder. But you can creat your own.
- *Test*: Use replay of the chartbook for proper notification in your Slack.
- *Run*: Host on a or remote server with SierraChart for one or multiple markets...

