let minerals = 0;
let mps = 0; // minerals per second

const mineralsDisplay = document.getElementById('score');
const mpsDisplay = document.getElementById('cps');
const mine = document.getElementById('mine');
const storeContainer = document.getElementById('store-container');

const facilities = [
    {
        name: '常総学院',
        cost: 15,
        mps: 0.1,
        count: 0
    },
    {
        name: '一心の母親',
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
    }
    
];

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
    }
}

// Initial render
renderStore();
updateMinerals(); // Display initial 0 minerals
updateMPS();     // Display initial 0 mps

mine.addEventListener('click', (e) => {
    minerals++;
    updateMinerals();

    const plusOne = document.createElement('div');
    plusOne.innerHTML = '+1 Issin';
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
});
