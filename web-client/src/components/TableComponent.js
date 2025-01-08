// TableComponent.js
import React from 'react';
import { ReactComponent as PokerTableSVG } from '../assets/poker-table.svg';
import BoardComponent from './BoardComponent';

const TableComponent = ({ board }) => {
    return (
        <div style={tableStyle}>
            <PokerTableSVG style={svgStyle} />
            <div style={boardStyle}>
                <BoardComponent board={board} />
            </div>
        </div>
    );
};

const tableStyle = {
    display: 'flex',
    justifyContent: 'center',
    alignItems: 'center',
    height: '80vh',
    width: '80vw',
    position: 'relative',
};

const svgStyle = {
    maxWidth: '90%',
    maxHeight: '90%',
};

const boardStyle = {
    display: 'flex',
    position: 'absolute',
    top: '50%',
    left: '50%',
    transform: 'translate(-50%, -50%)',
    width: '80%',
    height: '50%',
    display: 'flex',
    justifyContent: 'center',
    alignItems: 'center',
    gap: '1.5vw',
};

export default TableComponent;
