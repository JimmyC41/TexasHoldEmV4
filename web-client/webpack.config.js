const path = require('path');

module.exports = {
  mode: 'development',
  entry: ['./generated/texas_holdem_grpc_web_pb.js', './generated/texas_holdem_pb.js', './index.js'],
  output: {
    filename: 'bundle.js',
    path: path.resolve(__dirname, 'dist'),
  },
  module: {
    rules: [
      {
        test: /\.jsx$/,
        exclude: /node_modules/,
        use: 'babel-loader',
      },
    ],
  },
  resolve: {
    extensions: ['.js', '.jsx'],
  },
  devServer: {
    static: './dist',
    // port: 3000
  },
};
