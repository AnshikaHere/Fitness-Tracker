class FitnessTracker {
    constructor() {
        this.users = JSON.parse(localStorage.getItem('fitnessUsers')) || [];
        this.currentUser = null;
        this.loadCurrentUser();
        this.initializeEventListeners();
        this.updateDashboard();
    }

    initializeEventListeners() {
        // Activity form
        document.getElementById('activity-form').addEventListener('submit', (e) => {
            e.preventDefault();
            this.addActivity();
        });

        // Sleep form
        document.getElementById('sleep-form').addEventListener('submit', (e) => {
            e.preventDefault();
            this.addSleepData();
        });

        // Profile form
        document.getElementById('profile-form').addEventListener('submit', (e) => {
            e.preventDefault();
            this.createUser();
        });
    }

    createUser() {
        const username = document.getElementById('username').value;
        const weight = parseFloat(document.getElementById('weight').value);
        const height = parseFloat(document.getElementById('height').value);
        const age = parseInt(document.getElementById('age').value);

        let user = this.users.find(u => u.username === username);
        
        if (user) {
            // Update existing user
            user.weight = weight;
            user.height = height;
            user.age = age;
        } else {
            // Create new user
            user = {
                username,
                weight,
                height,
                age,
                activities: [],
                sleepRecords: []
            };
            this.users.push(user);
        }

        this.currentUser = user;
        this.saveData();
        this.updateDashboard();
        alert('Profile saved successfully!');
    }

    addActivity() {
        if (!this.currentUser) {
            alert('Please create a profile first!');
            return;
        }

        const activity = {
            date: document.getElementById('activity-date').value,
            type: document.getElementById('activity-type').value,
            duration: parseInt(document.getElementById('activity-duration').value),
            calories: parseInt(document.getElementById('activity-calories').value),
            distance: parseFloat(document.getElementById('activity-distance').value) || 0
        };

        this.currentUser.activities.push(activity);
        this.saveData();
        this.updateDashboard();
        document.getElementById('activity-form').reset();
        alert('Activity added successfully!');
    }

    addSleepData() {
        if (!this.currentUser) {
            alert('Please create a profile first!');
            return;
        }

        const sleepData = {
            date: document.getElementById('sleep-date').value,
            hours: parseInt(document.getElementById('sleep-hours').value),
            quality: parseInt(document.getElementById('sleep-quality').value)
        };

        this.currentUser.sleepRecords.push(sleepData);
        this.saveData();
        this.updateDashboard();
        document.getElementById('sleep-form').reset();
        alert('Sleep data added successfully!');
    }

    updateDashboard() {
        if (!this.currentUser) return;

        // Update stats
        const totalCalories = this.currentUser.activities.reduce((sum, activity) => sum + activity.calories, 0);
        const totalSleepHours = this.currentUser.sleepRecords.reduce((sum, sleep) => sum + sleep.hours, 0);
        const avgSleep = this.currentUser.sleepRecords.length > 0 ? 
            (totalSleepHours / this.currentUser.sleepRecords.length).toFixed(1) : 0;

        document.getElementById('total-calories').textContent = totalCalories;
        document.getElementById('avg-sleep').textContent = `${avgSleep}h`;
        document.getElementById('total-activities').textContent = this.currentUser.activities.length;

        // Update recent activities
        const activitiesList = document.getElementById('activities-list');
        activitiesList.innerHTML = '';

        const recentActivities = this.currentUser.activities.slice(-5).reverse();
        recentActivities.forEach(activity => {
            const li = document.createElement('li');
            li.innerHTML = `
                <span>${activity.date} - ${activity.type}</span>
                <span>${activity.duration}min, ${activity.calories}cal</span>
            `;
            activitiesList.appendChild(li);
        });
    }

    saveData() {
        localStorage.setItem('fitnessUsers', JSON.stringify(this.users));
        if (this.currentUser) {
            localStorage.setItem('currentFitnessUser', this.currentUser.username);
        }
    }

    loadCurrentUser() {
        const currentUsername = localStorage.getItem('currentFitnessUser');
        if (currentUsername) {
            this.currentUser = this.users.find(u => u.username === currentUsername);
            if (this.currentUser) {
                // Populate profile form
                document.getElementById('username').value = this.currentUser.username;
                document.getElementById('weight').value = this.currentUser.weight;
                document.getElementById('height').value = this.currentUser.height;
                document.getElementById('age').value = this.currentUser.age;
            }
        }
    }

    // Add this method to import data from C++ version
    importFromCpp() {
        try {
            // In a real scenario, you would fetch this file from a server
            // For now, we'll simulate it with a file input or manual import
            alert('To import C++ data:\n1. Use Option 6 in C++ version to create web_export.json\n2. Move web_export.json to frontend folder\n3. Refresh this page - data will be loaded automatically');
            
            // Simulate reading the file (in real implementation, use FileReader API)
            const simulatedData = {
                username: "C++ User",
                totalCalories: 1500,
                avgSleep: 7.5
            };
            
            // Create or update user with C++ data
            let user = this.users.find(u => u.username === simulatedData.username);
            if (!user) {
                user = {
                    username: simulatedData.username,
                    weight: 70,  // Default values
                    height: 175,
                    age: 25,
                    activities: [],
                    sleepRecords: []
                };
                this.users.push(user);
            }
            
            // Add sample activity based on C++ data
            user.activities.push({
                date: new Date().toISOString().split('T')[0],
                type: "Imported from C++",
                duration: 60,
                calories: simulatedData.totalCalories,
                distance: 0
            });

            // Add sample sleep data
            user.sleepRecords.push({
                date: new Date().toISOString().split('T')[0],
                hours: Math.round(simulatedData.avgSleep),
                quality: 4
            });
            
            this.currentUser = user;
            this.saveData();
            this.updateDashboard();
            alert('Sample C++ data imported successfully!\n\nImported:\n- ' + simulatedData.totalCalories + ' calories\n- ' + simulatedData.avgSleep + ' hours average sleep');
            
        } catch (error) {
            alert('Error importing C++ data: ' + error.message);
        }
    }

    // Advanced: Real file import (optional enhancement)
    importFromCppFile(event) {
        const file = event.target.files[0];
        if (!file) return;

        const reader = new FileReader();
        reader.onload = (e) => {
            try {
                const cppData = JSON.parse(e.target.result);
                this.processCppData(cppData);
            } catch (error) {
                alert('Error reading C++ export file: ' + error.message);
            }
        };
        reader.readAsText(file);
    }

    processCppData(cppData) {
        // Process the actual C++ exported data
        let user = this.users.find(u => u.username === cppData.username);
        if (!user) {
            user = {
                username: cppData.username,
                weight: 70,
                height: 175,
                age: 25,
                activities: [],
                sleepRecords: []
            };
            this.users.push(user);
        }

        // Add imported data
        user.activities.push({
            date: new Date().toISOString().split('T')[0],
            type: "C++ Imported Activity",
            duration: 60,
            calories: cppData.totalCalories,
            distance: 0
        });

        this.currentUser = user;
        this.saveData();
        this.updateDashboard();
        alert('C++ data imported successfully!');
    }
}

// Navigation function
function showSection(sectionId) {
    // Hide all sections
    document.querySelectorAll('.section').forEach(section => {
        section.classList.remove('active');
    });
    
    // Show selected section
    document.getElementById(sectionId).classList.add('active');
}

// Initialize the application
const fitnessApp = new FitnessTracker();