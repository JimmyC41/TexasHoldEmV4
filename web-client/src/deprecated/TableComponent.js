import React, { useEffect, useState } from 'react';
import { ReactComponent as PokerTableSVG } from '../assets/poker-table.svg';
import BoardComponent from './BoardComponent';
import PlayerComponent from './PlayerComponent';

const TableComponent = ({ gameState }) => {
    const { players, nextPlayerToAct, board } = gameState;
    const [tableSize, setTableSize] = useState({ width: 0, height: 0 });

    useEffect(() => {
        // Set the table size dynamically based on the SVG container's dimensions
        const tableContainer = document.getElementById('table-container');
        if (tableContainer) {
            setTableSize({
                width: tableContainer.offsetWidth,
                height: tableContainer.offsetHeight,
            });
        }
    }, [gameState]);

    // Calculate the player positions around the table
    const playerPositions = players.map((player, index) => {
        const angle = (index / players.length) * 2 * Math.PI; // Equidistant placement
        const x = tableSize.width / 2 + Math.cos(angle) * (tableSize.width / 3); // Adjust multiplier to scale better
        const y = tableSize.height / 2 + Math.sin(angle) * (tableSize.height / 3); // Adjust multiplier to scale better

        return {
            player,
            position: { x, y },
        };
    });

    // Calculate the position of the recent bet (number) for each player
    const getBetPosition = (player, position) => {
        const betAmount = player.recentBets;
        if (betAmount === 0) return null;

        const betDistance = 0.15 * tableSize.width; // Adjust this to make the bet amount appear closer or further away
        const angle = (players.findIndex(p => p.id === player.id) / players.length) * 2 * Math.PI;

        // Calculate position along the line from the player to the center of the table
        const x = position.x + Math.cos(angle) * betDistance;
        const y = position.y + Math.sin(angle) * betDistance;

        return { x, y };
    };

    return (
        <div style={tableStyle} id="table-container">
            <PokerTableSVG id="poker-table" style={svgStyle} />
            <div style={boardStyle}>
                <BoardComponent board={board} />
            </div>

            {playerPositions.map(({ player, position }, index) => {
                const isNextToAct = player.id === nextPlayerToAct.playerToAct;
                const isDealer = index === players.length - 1; // Last player is the dealer
                const betPosition = getBetPosition(player, position);

                return (
                    <div
                        key={player.id}
                        style={{
                            ...playerPositionStyle(position),
                            position: 'absolute', // Absolute positioning inside the table container
                        }}
                    >
                        <PlayerComponent
                            player={player}
                            isNextToAct={isNextToAct}
                            isDealer={isDealer}
                        />
                        
                        {/* Render the recent bet as a number if the player has a bet */}
                        {betPosition && (
                            <div
                                style={{
                                    position: 'absolute',
                                    left: `${betPosition.x}px`,
                                    top: `${betPosition.y}px`,
                                    transform: 'translate(-50%, -50%)',
                                    fontSize: '16px', // Adjust font size of the bet number
                                    fontWeight: 'bold',
                                    color: '#fff', // Color for the bet number
                                }}
                            >
                                {player.recentBets}
                            </div>
                        )}
                    </div>
                );
            })}
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
    overflow: 'hidden',
};

const svgStyle = {
    width: '100%',
    height: '100%',
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

const playerPositionStyle = (position) => ({
    left: `${position.x}px`,
    top: `${position.y}px`,
    transform: 'translate(-50%, -50%)', // Center the player component relative to the position
});

export default TableComponent;
