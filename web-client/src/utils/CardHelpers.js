export function getCardImagePath(suit, value) {
    const suitMap = {
      	1: 'hearts',
      	2: 'diamonds',
    	3: 'clubs',
    	4: 'spades'
    };
  
    const valueMap = {
    	2: '2',
      	3: '3',
      	4: '4',
      	5: '5',
      	6: '6',
      	7: '7',
      	8: '8',
      	9: '9',
      	10: '10',
      	11: 'jack',
      	12: 'queen',
      	13: 'king',
      	14: 'ace'
    };
  
    const suitStr = suitMap[suit] || 'unknown_suit';
    const valueStr = valueMap[value] || 'unknown_value';
  
    return `/assets/cards/${suitStr}_${valueStr}.svg`;
  }
  