class Tree {
    constructor(db) {
        this.DB = db;
    }

    async getAllTree() {
        let [sql] = await this.DB.execute(`SELECT threes.*, plants.name FROM threes JOIN plants ON threes.id_plants = plants.id`);
        return sql;
    }

    async createTree(nameTree) {
        try {
            const date = new Date();
            const formattedDate = date.toISOString().split('T')[0];

            // שלב 1: חפש עץ בטבלה plants לפי שם
            let [sql] = await this.DB.execute(`SELECT * FROM plants WHERE name = ?`, [nameTree]);
            console.log('Result from plants:', sql);  // הדפס את תוצאות השאילתה

            // אם העץ קיים בטבלת plants, הוסף אותו לטבלת threes
            if (sql.length > 0) {
                await this.DB.execute(`INSERT INTO threes(id_plants, date) VALUES(?,?);`, [sql[0].id, formattedDate]);
                console.log(`Tree added to threes with id: ${sql[0].id} and date: ${formattedDate}`);
            } else {
                // אם העץ לא קיים, הוסף אותו לטבלת plants ואז הוסף אותו לטבלת threes
                let [result] = await this.DB.execute(`INSERT INTO plants(name) VALUES(?);`, [nameTree]);
                console.log('New tree added to plants:', result);  // הדפס את תוצאות השאילתה

                // עכשיו השתמש ב-`insertId` כדי להוסיף את העץ לטבלת threes
                await this.DB.execute(`INSERT INTO threes(id_plants, date) VALUES(?,?);`, [result.insertId, formattedDate]);
                console.log(`Tree added to threes with id: ${result.insertId} and date: ${formattedDate}`);
            }
        } catch (error) {
            console.log('Error in createTree:', error);
        }
    }
    async deleteTree(idTree) {
        try {
            await this.DB.execute(`DELETE FROM plants WHERE id = (SELECT id_plants FROM threes WHERE id = ?)`, [idTree]);
        } catch (error) {
            console.log(error);
        }
    }

    async updateTreeName(idTree, newName) {
        try {
            await this.DB.execute(`UPDATE plants SET name = ? WHERE id = (SELECT id_plants FROM threes WHERE id = ?)`, [newName, idTree]);
        } catch (error) {
            console.log(error);
        }
    }
}

module.exports = Tree;
