class Tree{
    constructor(db){
        this.DB = db;
    }

    async getAllTree(){
        let [sql]= await this.DB.execute(`SELECT * FROM threes,plants WHERE id_plants = id`);
    }

    async createTree(nameTree){
        try {
            const date = new Date();
            const formattedDate = date.toISOString().split('T')[0];
            let [sql]= await this.DB.execute(`SELECT * FROM plants where name = ?`,[nameTree]);
            if(sql.length > 0){
                await this.DB.execute(`INSERT INTO threes(id_plants, date) VALUE(?,?);`,[sql[0].id, formattedDate]);
            }else{
                sql = await this.DB.execute(`INSERT INTO plants(name) VALUE(?);`,[nameTree]);
                await this.DB.execute(`INSERT INTO threes(id_plants, date) VALUE(?,?);`,[sql.insertId, formattedDate]);
                console.log(sql);
            }
        } catch (error) {
            console.log(error);
        }
    }


    async deleteTree(idTree){
        try {
            await this.DB.execute(`DELETE FROM threes WHERE id = ?`, [idTree]);

            let [plants] = await this.DB.execute(`SELECT * FROM threes WHERE id_plants = (SELECT id_plants FROM threes WHERE id = ?)`, [idTree]);

            if (plants.length === 0) {
                await this.DB.execute(`DELETE FROM plants WHERE id = (SELECT id_plants FROM threes WHERE id = ?)`, [idTree]);
        }catch(error){
            console.log(error);
        }
    }

    async updateTree(nameTree){
        try {

        }catch (error){
            console.log(error);
        }
    }


}

module.exports = Tree;