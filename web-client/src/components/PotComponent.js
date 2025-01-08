import React from 'react';
import '../styles.css';

const PotsComponent = ({ pots }) => {
    return (
        <div className="pot-container">
            <div> className="pots-list"</div>
                {pots.map((pot, index))}
        </div>
    )
};

export default PotsComponent;