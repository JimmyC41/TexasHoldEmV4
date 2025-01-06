import React, { useState } from 'react';
import { useDispatch } from 'react-redux';
import { gameStream } from '../grpc/streamingCalls'

const SubscribeGameComponent = ({ playerId }) => {
  const dispatch = useDispatch();
  const [isSubscribed, setIsSubscribed] = useState(false);
  const [stream, setStream] = useState(null);
  const [inputValue, setInputValue] = useState('');

  const handleInputChange = (event) => {
    setInputValue(event.target.value);  // Update input value as the user types
  };

  const handleSubscribe = () => {
    if (inputValue && !isSubscribed) {
      // Start receiving game events
      const newStream = gameStream(inputValue, dispatch);
      setStream(newStream);
      setIsSubscribed(true);
    }
  };

  const handleUnsubscribe = () => {
    if (stream) {
      // Stop receiving events by canceling the stream
      stream.cancel();
      setStream(null);
      setIsSubscribed(false);
    }
  };

  return (
    <div>
      <h3>Subscribe to Game Events</h3>
      <p>Player ID: {inputValue}</p>

      <input
        type="text"
        value={inputValue}  // Ensure this is a controlled input
        onChange={handleInputChange}  // Update state on input change
        placeholder="Enter Player ID"
      />
      
      {isSubscribed ? (
        <div>
          <p>Listening for game events...</p>
          <button onClick={handleUnsubscribe}>Unsubscribe</button>
        </div>
      ) : (
        <div>
          <p>Not subscribed to game events yet.</p>
          <button onClick={handleSubscribe}>Subscribe</button>
        </div>
      )}
    </div>
  );
};

export default SubscribeGameComponent;
