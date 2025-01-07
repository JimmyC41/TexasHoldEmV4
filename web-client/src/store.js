import { configureStore } from '@reduxjs/toolkit';
import rootReducer from './deprecated/reducers/RootReducer';

const store = configureStore({
  reducer: rootReducer,
});

export default store;