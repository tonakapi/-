let minerals = 0;
let mps = 0; // minerals per second

const mineralsDisplay = document.getElementById('score');
const mpsDisplay = document.getElementById('cps');
const mine = document.getElementById('mine');
const storeContainer = document.getElementById('store-container');

// Initial facilities data for reset purposes
const initialFacilities = [
    {
        name: '常総学院',
        cost: 15,
        mps: 0.1,
        count: 0
    },
    {
        name: 'おばあちゃん',
        cost: 100,
        mps: 1,
        count: 0
    },
    {
        name: '日本大学',
        cost: 1100,
        mps: 8,
        count: 0
    },
    {
        name: '水戸塾',
        cost: 12000,
        mps: 47,
        count: 0
    },
    {
        name: '足立理事長',
        cost: 130000,
        mps: 260,
        count: 0
    },
    {
        name: '靖国神社',
        cost: 500000,
        mps: 1000,
        count: 0
    },
    {
        name: '共産主義',
        cost: 1000000,
        mps: 1917,
        count: 0
    },
    {
        name: '一心補完計画',
        cost: 20000000,
        mps: 12345,
        count: 0
    },
    {
        name: 'プラズマ融合炉',
        cost: 330000000,
        mps: 50000,
        count: 0
    },
    {
        name: '時空間転移装置',
        cost: 5100000000,
        mps: 200000,
        count: 0
    }
];

let facilities = JSON.parse(JSON.stringify(initialFacilities)); // Deep copy for mutable array

// --- Game Logic Functions ---
function updateMinerals() {
    mineralsDisplay.innerText = Math.floor(minerals);
}

function updateMPS() {
    mpsDisplay.innerText = mps.toFixed(1);
}

function renderStore() {
    storeContainer.innerHTML = '';
    facilities.forEach((facility, index) => {
        const facilityElement = document.createElement('div');
        facilityElement.classList.add('upgrade'); // Reusing 'upgrade' class for styling
        if (minerals < facility.cost) {
            facilityElement.classList.add('disabled');
        }
        facilityElement.innerHTML = `
            <p>${facility.name}</p>
            <p>Cost: ${Math.floor(facility.cost)} Issins</p>
            <p>MPS: +${facility.mps}</p>
            <p>Count: ${facility.count}</p>
        `;
        facilityElement.addEventListener('click', () => buyFacility(index));
        storeContainer.appendChild(facilityElement);
    });
}

function buyFacility(index) {
    const facility = facilities[index];
    if (minerals >= facility.cost) {
        minerals -= facility.cost;
        mps += facility.mps;
        facility.count++;
        facility.cost *= 1.15; // Cost increases by 15%
        updateMinerals();
        updateMPS();
        renderStore();
        saveGame(); // Save game after every purchase
    }
}

// --- Save/Load/Reset Functions ---
const SAVE_KEY = 'isshinClickerSave';

function saveGame() {
    const gameSave = {
        minerals: minerals,
        mps: mps,
        facilities: facilities
    };
    localStorage.setItem(SAVE_KEY, JSON.stringify(gameSave));
    console.log('Game Saved!');
}

function loadGame() {
    const savedData = localStorage.getItem(SAVE_KEY);
    if (savedData) {
        const gameSave = JSON.parse(savedData);
        minerals = gameSave.minerals;
        mps = gameSave.mps !== undefined ? gameSave.mps : 0;
        // Ensure facilities structure is consistent, add new ones if any
        gameSave.facilities.forEach(savedFacility => {
            const index = initialFacilities.findIndex(f => f.name === savedFacility.name);
            if (index !== -1) {
                facilities[index] = savedFacility;
            } else {
                // Handle new facilities added since last save if necessary
                // For simplicity, we'll just use the initial one if not found in saved
                facilities.push(savedFacility); // Or handle merging differently
            }
        });
        console.log('Game Loaded!');
    } else {
        console.log('No saved game found, starting new game.');
        facilities = JSON.parse(JSON.stringify(initialFacilities)); // Start with initial facilities
    }

    // Recalculate MPS based on loaded facilities
    let totalMps = 0;
    facilities.forEach(facility => {
        totalMps += facility.mps * facility.count;
    });
    mps = totalMps; // Assign calculated totalMps to mps

    updateMinerals();
    updateMPS();
    renderStore();
}

function resetGame() {
    if (confirm('Are you sure you want to reset your game? All progress will be lost!')) {
        localStorage.removeItem(SAVE_KEY);
        minerals = 0;
        mps = 0;
        facilities = JSON.parse(JSON.stringify(initialFacilities)); // Reset to initial facilities
        updateMinerals();
        updateMPS();
        renderStore();
        console.log('Game Reset!');
    }
}

// --- Event Listeners and Initial Setup ---
// Initial render (will be updated by loadGame)
// renderStore(); // Moved to loadGame

mine.addEventListener('click', (e) => {
    const amountGained = Math.max(1, mps * 0.25); // Capture the amount gained
    minerals += amountGained; // Add captured amount to minerals
    updateMinerals();

    const plusOne = document.createElement('div');
    plusOne.innerHTML = `+${Math.floor(amountGained)} Issin`;
    plusOne.classList.add('plus-one');
    
    // Position the '+1' text at the cursor's location
    const mineRect = mine.getBoundingClientRect();
    plusOne.style.left = `${e.clientX - mineRect.left}px`;
    plusOne.style.top = `${e.clientY - mineRect.top}px`;
    
    const mineSection = document.getElementById('mine-section');
    mineSection.appendChild(plusOne);

    // Remove the '+1' element after the animation finishes
    setTimeout(() => {
        plusOne.remove();
    }, 1000);
});

setInterval(() => {
    minerals += mps / 10;
    updateMinerals();
    renderStore(); // Re-render store to update disabled state and costs
}, 100);

document.addEventListener('DOMContentLoaded', () => {
    const lineShareButton = document.getElementById('line-share-button');
    if (lineShareButton) {
        const url = encodeURIComponent(window.location.href);
        const lineUrl = `https://social-plugins.line.me/lineit/share?url=${url}`;
        lineShareButton.setAttribute('href', lineUrl);
    }

    // Add event listeners for save and reset buttons
    const saveButton = document.getElementById('save-game-button');
    const resetButton = document.getElementById('reset-game-button');

    if (saveButton) {
        saveButton.addEventListener('click', saveGame);
    }
    if (resetButton) {
        resetButton.addEventListener('click', resetGame);
    }

    loadGame(); // Load game state on page load
});
