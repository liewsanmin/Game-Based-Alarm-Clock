# Game-Based-Alarm-Clock
We are and San Min Liew and Joe Manion. We created a Game Based Alarm Clock using two Particle Photon boards. The first Photon is the "brain" and tells the second Photon when to turn the buzzer on and off. You set the alarm using your web browser by passing strings from the webpage to cloud functions associated with one of the Photons. When the first Photon determines that it is time to wake up it publishes an event using a Particle.publish() that the second Photon is subscribed to. The handler for this event triggers the code on the second Photon to star playing a melody and flashing some lights in random pattern. In order to turn the alarm off the user must match a pattern that is randomly generated. When the correct pattern is enter a new event is published and the handler for this event on the second Photon tells the buzzer to stop making noise and flashing lights.

The link to youtube can be found below 
https://www.youtube.com/watch?v=xfvp1TjCX2M
