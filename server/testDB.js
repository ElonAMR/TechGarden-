require('dotenv').config();
const db = require('./models/database'); // מחבר לקובץ של החיבור ל-DB

async function testConnection() {
    try {
        const [rows] = await db.execute('SELECT 1 + 1 AS result');
        console.log('✅ Database connected successfully! Result:', rows[0].result);
    } catch (error) {
        console.error('❌ Database connection failed:', error);
    }
}

testConnection().then(() => process.exit()).catch(() => process.exit(1));
