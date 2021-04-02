class Run:
    def __init__(self, start, part1):
        """
        this is the constructor for Run
        :param start: the starting index in memory to run the program from
        :param part1: the memory
        """
        self.brk = False
        self.address = None
        self.opcode = None
        self.memory = part1
        self.PC = int(start[:-1], 16)
        self.AC = 0x00
        self.XR = 0x00
        self.YR = 0x00
        self.SR = 0x00
        self.SP = 0x1FF
        self.flags = {'N': '0', 'V': '0', '-': '1', 'B': '0', 'D': '0', 'I': '0', 'Z': '0', 'C': '0'}
        self.opperand = ' -- --'

        self.ops = {0x69: self.ADC, 0x65: self.ADC, 0x75: self.ADC, 0x6D: self.ADC, 0x7D: self.ADC, 0x79: self.ADC,
                    0x61: self.ADC, 0x71: self.ADC, 0x29: self.AND, 0x25: self.AND, 0x35: self.AND, 0x2D: self.AND,
                    0x3D: self.AND, 0x39: self.AND, 0x21: self.AND, 0x31: self.AND, 0x0a: self.ASL, 0x06: self.ASL,
                    0x16: self.ASL, 0x0E: self.ASL, 0x1E: self.ASL, 0x90: self.BCC, 0xB0: self.BCS, 0xF0: self.BEQ,
                    0x24: self.BIT, 0x2C: self.BIT, 0x30: self.BMI, 0xD0: self.BNE, 0x10: self.BPL, 0x00: self.BRK,
                    0x50: self.BVC, 0x70: self.BVS, 0x18: self.CLC, 0xD8: self.CLD, 0x58: self.CLI, 0xB8: self.CLV,
                    0xC9: self.CMP, 0xC5: self.CMP, 0xD5: self.CMP, 0xCD: self.CMP, 0xDD: self.CMP, 0xD9: self.CMP,
                    0xC1: self.CMP, 0xD1: self.CMP, 0xE0: self.CPX, 0xE4: self.CPX, 0xEC: self.CPX, 0xC0: self.CPY,
                    0xC4: self.CPY, 0xCC: self.CPY, 0xC6: self.DEC, 0xD6: self.DEC, 0xCE: self.DEC, 0xDE: self.DEC,
                    0xCA: self.DEX, 0x88: self.DEY, 0x49: self.EOR, 0x45: self.EOR, 0x55: self.EOR, 0x4D: self.EOR,
                    0x5D: self.EOR, 0x59: self.EOR, 0x41: self.EOR, 0x51: self.EOR, 0xE6: self.INC, 0xF6: self.INC,
                    0xEE: self.INC, 0xFE: self.INC, 0xE8: self.INX, 0xC8: self.INY, 0x4C: self.JMP, 0x6C: self.JMP,
                    0x20: self.JSR, 0xA9: self.LDA, 0xA5: self.LDA, 0xB5: self.LDA, 0xAD: self.LDA, 0xBD: self.LDA,
                    0xB9: self.LDA, 0xA1: self.LDA, 0xB1: self.LDA, 0xA2: self.LDX, 0xA6: self.LDX, 0xB6: self.LDX,
                    0xAE: self.LDX, 0xBE: self.LDX, 0xA0: self.LDY, 0xA4: self.LDY, 0xB4: self.LDY, 0xAC: self.LDY,
                    0xBC: self.LDY, 0x4A: self.LSR, 0x46: self.LSR, 0x56: self.LSR, 0x4E: self.LSR, 0x5E: self.LSR,
                    0xEA: self.NOP, 0x09: self.ORA, 0x05: self.ORA, 0x15: self.ORA, 0x0D: self.ORA, 0x1D: self.ORA,
                    0x19: self.ORA, 0x01: self.ORA, 0x11: self.ORA, 0x48: self.PHA, 0x08: self.PHP, 0x68: self.PLA,
                    0x28: self.PLP, 0x2A: self.ROL, 0x26: self.ROL, 0x36: self.ROL, 0x2E: self.ROL, 0x3E: self.ROL,
                    0x6A: self.ROR, 0x66: self.ROR, 0x76: self.ROR, 0x6E: self.ROR, 0x7E: self.ROR, 0x40: self.RTI,
                    0x60: self.RTS, 0xE9: self.SBC, 0xE5: self.SBC, 0xF5: self.SBC, 0xED: self.SBC, 0xFD: self.SBC,
                    0xF9: self.SBC, 0xE1: self.SBC, 0xF1: self.SBC, 0x38: self.SEC, 0xF8: self.SED, 0x78: self.SEI,
                    0x85: self.STA, 0x95: self.STA, 0x8D: self.STA, 0x9D: self.STA, 0x99: self.STA, 0x81: self.STA,
                    0x91: self.STA, 0x86: self.STX, 0x96: self.STX, 0x8E: self.STX, 0x84: self.STY, 0x94: self.STY,
                    0x8C: self.STY, 0xAA: self.TAX, 0xA8: self.TAY, 0xBA: self.TSX, 0x8A: self.TXA, 0x9A: self.TXS,
                    0x98: self.TYA}

    def runProg(self):
        """
        this funtion iterates through the memory from the given starting point until it reaches the break code(0x00).
        it calls the function associated with the opcode located in memory at the current PC to perform the required
        operations. after each operation is completed, the resulting state of the emulator is displayed on each newline
        in the form of 'PC  OPC  INS   AMOD OPRND  AC XR YR SP NV-BDIZC'. if no operands are given, a '--' is printed
        in their place.
        :return:
        """
        print(' PC  OPC  INS   AMOD OPRND  AC XR YR SP NV-BDIZC')
        while True:
            self.opcode = self.memory[self.PC]
            if self.PC < 0xFFF:
                print(' ', end='')
            print('{:03X}  {:02X}  '.format(self.PC, self.memory[self.PC]), end='')
            func = self.ops[self.opcode]
            func()
            print(self.opperand, end='  ')
            print('{:02X} {:02X} {:02X} {:02X}'.format(self.AC, self.XR, self.YR, self.SP & 0xFF),
                  ''.join(self.flags.values()))

            if self.brk:
                return
            self.PC += 1
            self.opperand = ' -- --'

    def implied(self, name, bit, val):
        print(name + '   impl', end='')
        self.flags[bit] = val

    def reletative(self, bit, val, s):
        print(s + '    rel', end='')
        self.PC += 1
        self.opperand = ' ' + hex(self.memory[self.PC])[2:].zfill(2).upper() + ' --'
        if self.flags[bit] == val:
            offset = self.memory[self.PC]
            if offset > 127:
                offset -= 256
            self.PC += offset

    def immediate(self):
        print('      #', end='')
        self.PC += 1
        self.opperand = ' ' + hex(self.memory[self.PC])[2:].zfill(2).upper() + ' --'
        return self.memory[self.PC]

    def zeropage(self, amod, offset=0):
        print(amod, end='')
        self.PC += 1
        self.opperand = ' ' + hex(self.memory[self.PC])[2:].zfill(2).upper() + ' --'
        self.address = self.memory[self.PC] + offset
        if self.address > 0xFF:
            self.address -= 0xFE
        return self.memory[self.address]

    def absolute(self, amod, offset=0):
        # addr = int.from_bytes([op1, op2], 'little')
        print(amod, end='')
        self.PC += 1
        self.opperand = ' ' + hex(self.memory[self.PC])[2:].zfill(2) + ' ' + hex(self.memory[self.PC + 1])[2:].zfill(2)
        self.opperand = self.opperand.upper()
        HH = self.memory[self.PC]
        self.PC += 1
        LL = self.memory[self.PC]
        self.address = int.from_bytes([HH, LL], 'little') + offset
        return self.memory[self.address]

    def inderectX(self):
        print('  x,ind', end='')
        self.PC += 1
        self.opperand = ' ' + hex(self.memory[self.PC])[2:].zfill(2).upper() + ' --'
        address = (self.memory[self.PC] + self.XR) & 0xFF
        LL = self.memory[address + 1]
        HH = self.memory[address]
        self.address = int.from_bytes([HH, LL], 'little')
        return self.memory[self.address]

    def inderectY(self):
        print('  ind,y', end='')
        self.PC += 1
        self.opperand = ' ' + hex(self.memory[self.PC])[2:].zfill(2).upper() + ' --'
        address = self.memory[self.PC]
        HH = self.memory[address]
        LL = self.memory[address + 1]
        self.address = self.address = int.from_bytes([HH, LL], 'little') + self.YR
        return self.memory[self.address]

    def setM(self, imm, zpg, zpgx, abs0, absx, absy, indx, zpgy):
        if self.opcode == imm:
            return self.immediate()
        if self.opcode == zpg:
            return self.zeropage('    zpg')
        if self.opcode == zpgx:
            return self.zeropage('  zpg,x', self.XR)
        if self.opcode == zpgy:
            return self.zeropage('  zpg,y', self.YR)
        if self.opcode == abs0:
            return self.absolute('    abs')
        if self.opcode == absx:
            return self.absolute('  abs,x', self.XR)
        if self.opcode == absy:
            return self.absolute('  abs,y', self.YR)
        if self.opcode == indx:
            return self.inderectX()
        # else
        return self.inderectY()

    def twosComp(self, number):
        num1s = ~number
        num2s = num1s + 1
        return num2s

    def ADC(self):
        """
         Add Memory to Accumulator with Carry
         A + M + C -> A, C      N Z C I D V
                                + + + - - +
         addressing     assembler    opc     bytes
         -------------------------------------
         immediate      ADC #oper    69      2      <--C Grade
         zeropage       ADC oper     65      2      <--C Grade
         zeropage,X     ADC oper,X   75      2
         absolute       ADC oper     6D      3
         absolute,X     ADC oper,X   7D      3
         absolute,Y     ADC oper,Y   79      3
         (indirect,X)   ADC (oper,X) 61      2
         (indirect),Y   ADC (oper),Y 71      2
        :return:
        """
        print('ADC', end='')
        carry = int(self.flags['C'])
        #      (self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0x69, 0x65, 0x75, 0x6D, 0x7D, 0x79, 0x61, None)
        self.setoverflow(self.AC, M)
        total = self.AC + M + carry
        self.flags['C'] = '1' if len(bin(total)[2:]) > 8 else '0'
        self.AC = self.fix(total & 0xFF)

    def AND(self):
        """
         AND Memory with Accumulator
         A AND M -> A       N Z C I D V
                            + + - - - -
         addressing     assembler    opc     bytes
         -------------------------------------
         immediate      AND #oper    29      2
         zeropage       AND oper     25      2
         zeropage,X     AND oper,X   35      2
         absolute       AND oper     2D      3
         absolute,X     AND oper,X   3D      3
         absolute,Y     AND oper,Y   39      3
         (indirect,X)   AND (oper,X) 21      2
         (indirect),Y   AND (oper),Y 31      2
        :return:
        """
        print('AND', end='')
        #      (self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0x29, 0x25, 0x35, 0x2D, 0x3D, 0x39, 0x21, None)
        self.AC = self.fix((self.AC & M) & 0xFF)

    def ASL(self):
        """
         Shift Left One Bit (Memory or Accumulator)
         C <- [76543210] <- 0   N Z C I D V
                                + + + - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         accumulator    ASL A       0A      1
         zeropage       ASL oper    06      2
         zeropage,X     ASL oper,X  16      2
         absolute       ASL oper    0E      3
         absolute,X     ASL oper,X  1E      3
         """
        print('ASL', end='')
        if self.opcode == 0x0A:
            print('      A', end='')
            self.flags['C'] = str((self.AC & 0xFF) >> 7)
            self.AC = self.fix((self.AC << 1) & 0xFF)
            return
        #   self.setM(imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0x06, 0x16, 0x0E, 0x1E, None, None, None)
        self.flags['C'] = str((M & 0xFF) >> 7)
        self.memory[self.address] = self.fix((M << 1) & 0xFF)

    def BCC(self):
        """
         Branch on Carry Clear
         branch on C = 0    N Z C I D V
                            - - - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         relative       BCC oper    90      2
        :return:
        """
        self.reletative('C', '0', 'BCC')

    def BCS(self):
        """
         Branch on Carry Set
         branch on C = 1    N Z C I D V
                            - - - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         relative       BCS oper    B0      2
        :return:
        """
        self.reletative('C', '1', 'BCS')

    def BEQ(self):
        """
         Branch on Result Zero
         branch on Z = 1    N Z C I D V
                            - - - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         relative       BEQ oper    F0      2
        :return:
        """
        self.reletative('Z', '1', 'BEQ')

    def BIT(self):
        """
         Test Bits in Memory with Accumulator
         bits 7 and 6 of operand are transferred to bit 7 and 6
         of SR (N,V); the zeroflag is set to the result of operand
         AND accumulator.
         A AND M, M7 -> N, M6 -> V      N Z C I D V
                                       M7 + - - - M6
         addressing     assembler   opc     bytes
         -------------------------------------
         zeropage       BIT oper    24      2
         absolute       BIT oper    2C      3
        :return:
        """
        print('BIT', end='')
        #   self.setM(imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0x24, None, 0x2C, None, None, None, None)
        self.flags['N'] = str((M & 0x80) >> 7)
        self.flags['V'] = str((M & 0x64) >> 6)
        self.flags['Z'] = '1' if M & self.AC == 0 else '0'

    def BMI(self):
        """
         Branch on Result Minus
         branch on N = 1    N Z C I D V
                            - - - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         relative       BMI oper    30      2
        :return:
        """
        self.reletative('N', '1', 'BMI')

    def BNE(self):
        """
        Branch on Result not Zero
         branch on Z = 0    N Z C I D V
                            - - - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         relative       BNE oper    D0      2
        :return:
        """
        self.reletative('Z', '0', 'BNE')

    def BPL(self):
        """
        BPL Branch on Result Plus
         branch on N = 0    N Z C I D V
                            - - - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         relative       BPL oper    10      2
        :return:
        """
        self.reletative('N', '0', 'BPL')

    def BRK(self):
        """
        BRK Force Break
         interrupt,             N Z C I D V B
         push PC+2, push SR     - - - 1 - - 1
         addressing     assembler   opc     bytes
         -------------------------------------
         implied        BRK         00      1
         """
        print('BRK   impl', end='')
        memval = self.PC + 2
        self.memory[self.SP] = (memval & 0xFF00) >> 8  # high byte
        self.SP -= 1
        self.memory[self.SP] = memval & 0xFF  # low byte
        self.SP -= 1
        self.flags['B'] = '1'
        self.flags['I'] = '1'
        self.memory[self.SP] = int(''.join(self.flags.values()), 2)
        self.SP -= 1
        self.brk = True

    def BVC(self):
        """
        BVC Branch on Overflow Clear
         branch on V = 0    N Z C I D V
                            - - - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         relative       BVC oper    50      2
        :return:
        """
        self.reletative('V', 'O', 'BVC')

    def BVS(self):
        """
        BVS Branch on Overflow Set
         branch on V = 1    N Z C I D V
                            - - - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         relative       BVS oper    70      2
        :return:
        """
        self.reletative('V', '1', 'BVS')

    def CLC(self):
        """
        CLC Clear Carry Flag
         0 -> C     N Z C I D V
                    - - 0 - - -
         addressing assembler opc bytes
         -------------------------------------
         implied    CLC       18  1
        """
        self.implied('CLC', 'C', '0')

    def CLD(self):
        """
        CLD Clear Decimal Mode
         0 -> D     N Z C I D V
                    - - - - 0 -
         addressing assembler opc bytes
         -------------------------------------
         implied CLD D8 1
        """
        self.implied('CLD', 'D', '0')

    def CLI(self):
        """
        CLI Clear Interrupt Disable Bit
        0 -> I              N Z C I D V
                            - - - 0 - -
        addressing assembler opc bytes
        -------------------------------------
        implied CLI 58 1
        """
        self.implied('CLI', 'I', '0')

    def CLV(self):
        """
        CLV Clear Overflow Flag
        0 -> V      N Z C I D V
                    - - - - - 0
        addressing assembler opc bytes
        -------------------------------------
        implied    CLV       B8    1
        """
        self.implied('CLV', 'V', '0')

    def CMP(self):
        """
        CMP Compare Memory with Accumulator
         A - M                  N Z C I D V
                                + + + - - -
         addressing     assembler     opc     bytes
         -------------------------------------
         immediate      CMP #oper     C9      2
         zeropage       CMP oper      C5      2
         zeropage,X     CMP oper,X    D5      2
         absolute       CMP oper      CD      3
         absolute,X     CMP oper,X    DD      3
         absolute,Y     CMP oper,Y    D9      3
         (indirect,X)   CMP (oper,X)  C1      2
         (indirect),Y   CMP (oper),Y  D1      2
        :return:
        """
        print('CMP', end='')
        #            (imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0xC9, 0xC5, 0xD5, 0xCD, 0xDD, 0xD9, 0xC1, None)
        self.setFlags(self.AC, M)

    def CPX(self):
        """
        CPX Compare Memory and Index X
        X - M       N Z C I D V
                    + + + - - -
        addressing      assembler   opc     bytes
        -------------------------------------
        Immediate       CPX #oper   E0      2
        zeropage        CPX oper    E4      2
        absolute        CPX oper    EC      3
        :return:
        """
        print('CPX', end='')
        #            (imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0xE0, 0xE4, None, 0xEC, None, None, None, None)
        self.setFlags(self.XR, M)

    def CPY(self):
        """
        CPY Compare Memory and Index Y
        Y - M       N Z C I D V
                    + + + - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        immediate   CPY #oper   C0      2
        zeropage    CPY oper    C4      2
        absolute    CPY oper    CC      3
        :return:
        """
        print('CPY', end='')
        #            (imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0xC0, 0xC4, None, 0xCC, None, None, None, None)
        self.setFlags(self.YR, M)

    def DEC(self):
        """
        DEC Decrement Memory by One
        M - 1 -> M      N Z C I D V
                        + + - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        zeropage    DEC oper    C6      2
        zeropage,X  DEC oper,X  D6      2
        absolute    DEC oper    CE      3
        absolute,X  DEC oper,X  DE      3
        :return:
        """
        print('DEC', end='')
        #      (self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0xC6, 0xD6, 0xCE, 0xDE, None, None, None)

        self.memory[self.address] = self.fix((M - 1) & 0xFF)

    def DEX(self):
        """
       DEX Decrement Index X by One
        X - 1 -> X     N Z C I D V
                       + + - - - -
        addressing     assembler   opc     bytes
        -------------------------------------
        implied        DEC         CA      1
       """
        print('DEX   impl', end='')
        self.XR = self.fix(self.XR - 1)

    def DEY(self):
        """
        DEY Decrement Index Y by One
         Y - 1 -> Y     N Z C I D V
                        + + - - - -
         addressing assembler opc bytes
         -------------------------------------
         implied    DEC       88  1
        """
        print('DEY   impl', end='')
        self.YR = self.fix(self.YR - 1)

    def EOR(self):
        """
        EOR Exclusive-OR Memory with Accumulator
        A EOR M -> A        N Z C I D V
                            + + - - - -
        addressing      assembler       opc     bytes
        -------------------------------------
        immediate       EOR #oper       49      2
        zeropage        EOR oper        45      2
        zeropage,X      EOR oper,X      55      2
        absolute        EOR oper        4D      3
        absolute,X      EOR oper,X      5D      3
        absolute,Y      EOR oper,Y      59      3
        (indirect,X)    EOR (oper,X)    41      2
        (indirect),Y    EOR (oper),Y    51      2
        :return:
        """
        # setM(self, imm, zpg=None, zpgx=None, abs0=None, absx=None, absy=None, indx=None, zpgy=None)
        print('EOR', end='')
        #  setM(self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0x49, 0x45, 0x55, 0x4D, 0x5D, 0x59, 0x41, None)
        self.AC = self.fix((self.AC ^ M) & 0xFF)

    def INC(self):
        """
        INC Increment Memory by One
        M + 1 -> M      N Z C I D V
                        + + - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        zeropage    INC oper    E6      2
        zeropage,X  INC oper,X  F6      2
        absolute    INC oper    EE      3
        absolute,X  INC oper,X  FE      3
        :return:
        """
        print('INC', end='')
        #  setM(self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0xE6, 0xF6, 0xEE, 0xFE, None, None, None)
        self.memory[self.address] = self.fix((M + 1) & 0xFF)

    def INX(self):
        """
        INX Increment Index X by One
         X + 1 -> X     N Z C I D V
                        + + - - - -
         addressing     assembler    opc    bytes
         -------------------------------------
         implied        INX          E8     1
        """
        print('INX   impl', end='')
        self.XR = self.fix(self.XR + 1)

    def INY(self):
        """
        INY Increment Index Y by One
         Y + 1 -> Y     N Z C I D V
                        + + - - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         implied        INY         C8      1
        """
        print('INY   impl', end='')
        self.YR = self.fix(self.YR + 1)

    def JMP(self):
        """
        JMP Jump to New Location
        (PC+1) -> PCL       N Z C I D V
        (PC+2) -> PCH       - - - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        absolute    JMP oper    4C      3
        indirect    JMP (oper)  6C      3
        :return:
        """
        print('JMP', end='')
        # setM(self, imm, zpg, zpgx, abs0, absx, absy, indx, zpgy)
        if self.opcode == 0x4C:
            self.absolute('    abs')
            self.PC = self.address - 1

        else:  # self.opcode == 0x6C
            HH = self.absolute('    ind')
            LL = self.memory[self.address + 1]
            self.PC = int.from_bytes([HH, LL], 'little') - 1

    def JSR(self):
        """
        Jump to New Location Saving Return Address
        push (PC+2),        N Z C I D V
        (PC+1) -> PCL       - - - - - -
        (PC+2) -> PCH
        addressing      assembler   opc     bytes
        -------------------------------------
        absolute        JSR oper    20      3
        :return:
        """
        print('JSR', end='')
        # push PC to stack
        store = self.PC + 2
        self.memory[self.SP] = (store & 0xFF00) >> 8  # high byte
        self.SP -= 1
        self.memory[self.SP] = store & 0xFF  # low byte
        self.SP -= 1
        # set new PC
        temp = self.absolute('    abs')
        self.PC = self.address - 1

    def LDA(self):
        """
        Load Accumulator with Memory
        M -> A      N Z C I D V
                    + + - - - -
        addressing      assembler       opc     bytes
        -------------------------------------
        immediate       LDA #oper       A9      2
        zeropage        LDA oper        A5      2
        zeropage,X      LDA oper,X      B5      2
        absolute        LDA oper        AD      3
        absolute,X      LDA oper,X      BD      3
        absolute,Y      LDA oper,Y      B9      3
        (indirect,X)    LDA (oper,X)    A1      2
        (indirect),Y     LDA (oper),Y   B1      2
        :return:
        """
        print('LDA', end='')
        #  setM(self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0xA9, 0xA5, 0xB5, 0xAD, 0xBD, 0xB9, 0xA1, None)
        self.AC = self.fix(M & 0xFF)

    def LDX(self):
        """
        Load Index X with Memory
        M -> X      N Z C I D V
                    + + - - - -
        addressing      assembler   opc     bytes
        -------------------------------------
        immediate       LDX #oper   A2      2
        zeropage        LDX oper    A6      2
        zeropage,Y      LDX oper,Y  B6      2
        absolute        LDX oper    AE      3
        absolute,Y      LDX oper,Y  BE      3
        :return:
        """
        print('LDX', end='')
        #  setM(self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0xA2, 0xA6, None, 0xAE, None, 0xBE, None, 0xB6)
        self.XR = self.fix(M & 0xFF)

    def LDY(self):
        """
        Load Index X with Memory
        M -> Y      N Z C I D V
                    + + - - - -
        addressing      assembler   opc     bytes
        -------------------------------------
        immediate       LDY #oper   A0      2
        zeropage        LDY oper    A4      2
        zeropage,X      LDY oper,X  B4      2
        absolute        LDY oper    AC      3
        absolute,X      LDY oper,X  BC      3
        :return:
        """
        print('LDY', end='')
        #  setM(self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0xA0, 0xA4, 0xB4, 0xAC, 0xBC, None, None, None)
        self.YR = self.fix(M & 0xFF)

    def LSR(self):
        """
        LSR Shift One Bit Right (Memory or Accumulator)
         0 -> [76543210] -> C   N Z C I D V
                                - + + - - -
         addressing     assembler   opc     bytes
         -------------------------------------
         accumulator    LSR A       4A      1
         zeropage       LSR oper    46      2
         zeropage,X     LSR oper,X  56      2
         absolute       LSR oper    4E      3
         absolute,X     LSR oper,X  5E      3
        """
        print('LSR', end='')
        if self.opcode == 0x4A:
            print('      A', end='')
            self.flags['C'] = str(self.AC & 0x1)
            self.AC = self.fix((self.AC >> 1) & 0xFF)
            return

        #  setM(self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0x46, 0x56, 0x4E, 0x5E, None, None, None)
        self.flags['C'] = str(M & 0x1)
        self.memory[self.address] = self.fix((M >> 1) & 0xFF)

    def NOP(self):
        """
        NOP No Operation
        ---         N Z C I D V
                    - - - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     NOP         EA      1
        """
        print('NOP   impl', end='')

    def ORA(self):
        """
        OR Memory with Accumulator
        A OR M -> A         N Z C I D V
                            + + - - - -
        addressing      assembler       opc     bytes
        -------------------------------------
        immediate       ORA #oper       09      2
        zeropage        ORA oper        05      2
        zeropage,X      ORA oper,X      15      2
        absolute        ORA oper        0D      3
        absolute,X      ORA oper,X      1D      3
        absolute,Y      ORA oper,Y      19      3
        (indirect,X)    ORA (oper,X)    01      2
        (indirect),Y    ORA (oper),Y    11      2
        :return:
        """
        print('ORA', end='')
        #  setM(self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0x09, 0x05, 0x15, 0x0D, 0x1D, 0x19, 0x01, None)
        self.AC = self.fix((self.AC | M) & 0xFF)

    def PHA(self):
        """
        PHA Push Accumulator on Stack
        push A         N Z C I D V
                        - - - - - -
        addressing     assembler   opc     bytes
        --------------------------------------
        implied        PHA         48      1
        """
        print('PHA   impl', end='')
        self.memory[self.SP] = self.AC
        self.SP -= 1

    def PHP(self):
        """
        PHP Push Processor Status on Stack
        push SR        N Z C I D V
                        - - - - - -
        addressing     assembler   opc     bytes
        -------------------------------------
        implied        PHP         08      1
        """
        print('PHP   impl', end='')
        self.memory[self.SP] = int(''.join(self.flags.values()), 2)
        self.SP -= 1

    def PLA(self):
        """
        PLA Pull Accumulator from Stack
        pull A      N Z C I D V
                    + + - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     PLA         68      1
        """
        print('PLA   impl', end='')
        self.SP += 1
        self.AC = self.fix(self.memory[self.SP])
        self.memory[self.SP] = 0

    def PLP(self):
        """
        PLP Pull Processor Status from Stack
        pull SR     N Z C I D V
                    from stack
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     PHP         28      1
        """
        print('PLP   impl', end='')
        self.SP += 1
        binarystring = bin(self.memory[self.SP])[2:].zfill(8)
        for i, v in enumerate('NV-BDIZC'):
            self.flags[v] = binarystring[i]
        self.memory[self.SP] = 0

    def ROL(self):
        """
        ROL Rotate One Bit Left (Memory or Accumulator)
        C <- [76543210] <- C    N Z C I D V
                                + + + - - -
        addressing      assembler   opc     bytes
        -------------------------------------
        accumulator     ROL A       2A      1
        zeropage        ROL oper    26      2
        zeropage,X      ROL oper,X  36      2
        absolute        ROL oper    2E      3
        absolute,X      ROL oper,X  3E      3
        """
        print('ROL', end='')
        carry = int(self.flags['C'])  # save old flag
        if self.opcode == 0x2A:
            print('      A', end='')
            self.AC <<= 1
            self.flags['C'] = str(self.AC >> 8)  # set new flag
            self.AC = self.fix((self.AC | carry) & 0xFF)
            return

        #        setM(imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0x26, 0x36, 0x2E, 0x3E, None, None, None)
        M <<= 1
        self.flags['C'] = str(M >> 8)  # set new flag
        self.memory[self.address] = self.fix((M | carry) & 0xFF)

    def ROR(self):
        """
        ROR Rotate One Bit Right (Memory or Accumulator)
        C -> [76543210] -> C    N Z C I D V
                                + + + - - -
        addressing      assembler   opc     bytes
        --------------------------------------
        accumulator     ROR A       6A      1
        zeropage        ROR oper    66      2
        zeropage,X      ROR oper,X  76      2
        absolute        ROR oper    6E      3
        absolute,X      ROR oper,X  7E      3
        """
        print('ROR', end='')
        carry = int(self.flags['C'])  # save old flag
        if self.opcode == 0x6A:
            print('      A', end='')
            self.flags['C'] = str(self.AC & 1)  # set new flag
            self.AC >>= 1
            self.AC = self.fix(self.AC | (carry << 7))
            return
        #        setM(imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0x66, 0x76, 0x6E, 0x7E, None, None, None)
        self.flags['C'] = str(M & 1)  # set new flag
        M >>= 1
        self.memory[self.address] = self.fix(M | (carry << 7))

    def RTI(self):
        """
        Return from Interrupt
        pull SR, pull PC    N Z C I D V
                            from stack
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     RTI         40      1
        :return:
        """
        print('RTI   impl', end='')
        self.SP += 1
        binarystring = bin(self.memory[self.SP])[2:].zfill(8)
        for i, v in enumerate('NV-BDIZC'):
            self.flags[v] = binarystring[i]
        self.memory[self.SP] = 0

        self.SP += 1
        HH = self.memory[self.SP]
        self.memory[self.SP] = 0
        self.SP += 1
        LL = self.memory[self.SP]
        self.memory[self.SP] = 0

        self.PC = ((HH << 4) | LL) - 1

    def RTS(self):
        """
        Return from Subroutine
        pull PC, PC+1 -> PC     N Z C I D V
                                - - - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     RTS         60      1
        :return:
        """
        print('RTS   impl', end='')
        self.SP += 1
        LL = self.memory[self.SP]
        self.memory[self.SP] = 0
        self.SP += 1
        HH = self.memory[self.SP]
        self.memory[self.SP] = 0
        temp = int.from_bytes([LL, HH], 'little')

        self.PC = temp

    def SBC(self):
        """
        Subtract Memory from Accumulator with Borrow
        A - M - C -> A      N Z C I D V
                            + + + - - +
        addressing      assembler       opc     bytes
        -------------------------------------
        immediate       SBC #oper       E9      2
        zeropage        SBC oper        E5      2
        zeropage,X      SBC oper,X      F5      2
        absolute        SBC oper        ED      3
        absolute,X      SBC oper,X      FD      3
        absolute,Y      SBC oper,Y      F9      3
        (indirect,X)    SBC (oper,X)    E1      2
        (indirect),Y    SBC (oper),Y    F1      2
        :return:
        """
        print('SBC', end='')
        carry = int(self.flags['C'])
        #      (self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(0xE9, 0xE5, 0xF5, 0xED, 0xFD, 0xF9, 0xE1, None)
        self.flags['C'] = '1' if len(bin(self.AC - M - carry)[:2]) > 8 else '0'
        M = self.twosComp(M)
        carry = self.twosComp(carry)
        self.setoverflow(self.AC, M + carry)
        self.AC = self.fix((self.AC + M + carry) & 0xFF)

    def SEC(self):
        """
        SEC Set Carry Flag
        1 -> C      N Z C I D V
                    - - 1 - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     SEC         38      1
        """
        print('SEC   impl', end='')
        self.flags['C'] = '1'

    def SED(self):
        """
        SED Set Decimal Flag
        1 -> D      N Z C I D V
                    - - - - 1 -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     SED         F8      1
        :return:
        """
        print('SED   impl', end='')
        self.flags['D'] = '1'

    def SEI(self):
        """
        SEI Set Interrupt Disable Status
        1 -> I      N Z C I D V
                    - - - 1 - -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     SEI         78      1
        """
        print('SEI   impl', end='')
        self.flags['I'] = '1'

    def STA(self):
        """
       Store Accumulator in Memory
        A -> M          N Z C I D V
                        - - - - - -
        addressing      assembler       opc     bytes
        ---------------------------------------------
        zeropage        STA oper        85      2
        zeropage,X      STA oper,X      95      2
        absolute        STA oper        8D      3
        absolute,X      STA oper,X      9D      3
        absolute,Y      STA oper,Y      99      3
        (indirect,X)    STA (oper,X)    81      2
        (indirect),Y    STA (oper),Y    91      2
        :return:
        """
        print('STA', end='')
        #      (self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0x85, 0x95, 0x8D, 0x9D, 0x99, 0x81, None)
        self.memory[self.address] = self.AC

    def STX(self):
        """
        Store Index X in Memory
        X -> M      N Z C I D V
                    - - - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        zeropage    STX oper    86      2
        zeropage,Y  STX oper,Y  96      2
        absolute    STX oper    8E      3
        :return:
        """
        print('STX', end='')
        #      (self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0x86, None, 0x8E, None, None, None, 0x96)
        self.memory[self.address] = self.XR

    def STY(self):
        """
        Store Index Y in Memory
        Y -> M      N Z C I D V
                    - - - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        zeropage    STY oper    84      2
        zeropage,X  STY oper,X  94      2
        absolute    STY oper    8C      3
        :return:
        """
        print('STY', end='')
        #      (self, imm,  zpg,  zpgx, abs0, absx, absy, indx, zpgy)
        M = self.setM(None, 0x84, 0x94, 0x8C, None, None, None, None)
        self.memory[self.address] = self.YR

    def TAX(self):
        """
        TAX Transfer Accumulator to Index X
        A -> X          N Z C I D V
                        + + - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     TAX         AA      1
        """
        print('TAX   impl', end='')
        self.XR = self.fix(self.AC)

    def TAY(self):
        """
        TAY Transfer Accumulator to Index Y
        A -> Y      N Z C I D V
                    + + - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     TAY         A8      1
        """
        print('TAY   impl', end='')
        self.YR = self.fix(self.AC)

    def TSX(self):
        """
        TSX Transfer Stack Pointer to Index X
        SP -> X         N Z C I D V
                        + + - - - -
        addressing  assembler   opc     bytes
        -------------------------------------
        implied     TSX         BA      1
        """
        print('TSX   impl', end='')
        self.XR = self.fix(self.SP)

    def TXA(self):
        """
        TXA Transfer Index X to Accumulator
        X -> A          N Z C I D V
                        + + - - - -
        addressing     assembler   opc     bytes
        -------------------------------------
        implied        TXA         8A      1
        """
        print('TXA   impl', end='')
        self.AC = self.fix(self.XR)

    def TXS(self):
        """
        TXS Transfer Index X to Stack Register
        X -> SP         N Z C I D V
                        - - - - - -
        addressing      assembler   opc     bytes
        -------------------------------------
        implied         TXS         9A      1
        """
        print('TXS   impl', end='')
        self.SP = self.XR

    def TYA(self):
        """
        TYA Transfer Index Y to Accumulator
        Y -> A      N Z C I D V
                    + + - - - -
         addressing assembler   opc     bytes
         -------------------------------------
         implied    TYA         98      1
        """
        print('TYA   impl', end='')
        self.AC = self.fix(self.YR)

    def setFlags(self, num, memory):
        self.flags['N'] = self.flags['Z'] = self.flags['C'] = '0'
        compare = num + self.twosComp(memory)

        if num >= memory:
            self.flags['C'] = '1'

        if num == memory:
            self.flags['Z'] = '1'

        if memory != 0 and (compare & 0x80) >> 7 == 1:
            self.flags['N'] = '1'

    def fix(self, val):
        """
        this takes in a value that has had an operation done to it and circularly keeps in with in the range of
        unsigned 8 bits. then it sets the N flag to the value stored in the most significant bit. next it sets the
        Z flag to 1 if val == 0, otherwise it sets it to 0. finally it returns the value.
        :param val: the value being operated on
        :return: the value that was operated on
        """
        if val < 0X00:
            val = 0x100 + val
        elif val > 0xFF:
            val = 0x100 - val
        if val > 127:
            self.flags['N'] = '1'
        else:
            self.flags['N'] = '0'
        self.flags['Z'] = '1' if val == 0 else '0'
        return val

    def setoverflow(self, num1, num2):
        self.flags['V'] = '0'

        # If the sum of two numbers with the sign bits off yields a result number
        #    with the sign bit on, the "overflow" flag is turned on.
        x = num1 >> 7
        y = num2 >> 7
        z = num1 + num2

        # If sum is more than 8 bits, set flag
        # if z >> 8 != 0:                       <--SAVE
        #   self.flags['V'] = '1'

        z >>= 7

        if x + y == 0 and z == 1:
            self.flags['V'] = '1'

        # If the sum of two numbers with the sign bits on yields a result number
        #    with the sign bit off, the "overflow" flag is turned on.
        if x + y == 2 and z == 0:
            self.flags['V'] = '1'


"""
Legend to Flags: 
+ .... modified
- .... not modified
1 .... set
0 .... cleared
M6 .... memory bit 6
M7 .... memory bit 7

part2 TEST VALUES DO NOT DELETE
300: EA C8 98 48 E8 E8 8A 68 00
300: 88 E8 98 0A 2A 48 8A 6A A8 68 AA 00
300: CA CA CA CA CA CA CA CA CA CA CA 00 -> TEST fix()
300: 88 E8 98 0A 2A 48 8A 6A A8 68 08 18 CA 28 AA 00 -> TEST PHP/PLP
300: 88 E8 98 0A 2A 48 8A 6A A8 68 AA 4A 00 -> TEST LSR

part3 TEST VALUES DO NOT DELETE
test1 PASSED
000: 00 00 00 00 00 FF 00 00
100: 00 11 22 33 44 55 66 77
300: A2 01 A0 01 A9 05 85 01 8C 05 07 A1 00 86 02 A2 0A 8E 04 07 B1 01

test2 --PASSED
300: 69 10 A2 02 85 02 E6 02 A5 02 00
300R

test3 PASSED
300: A9 AA 49 55 C9 00 69 01 C9 01
300R

test4 PASSED
000: 01 03 05 07 09 0B 0D 0F
300: A5 02 25 07 A6 03 86 08 E6 08 46 00
300R
000.00F

test5 PASSED
000: 00 03 05 07 09 0B 0D 0F
008: 08 00 00 00 00 00 00 00
300: AD 09 03 6D 13 03 D0 02 00 05 6C 16 03 20 14 03 00 90 FA 05 60 00 11 03
300R

test6 PASSED
1000: 01 03 05 07 09 0B 0D 0F 00 02 04 06 08 0A 0C 0E 10 30 50 70 90 B0 D0 F0 00 20 40 60 80 A0 C0 E0
300: AD 00 10 0D 13 10 8D 20 10 6D 06 10 6D 10 10 2C 20 10 0E 1D 10 6E 09 10
300R
1000.1027

test7
300: A9 01 85 00 18 2A A5 00 8D 00 80 A2 03 A0 03 88 D0 FD CA D0 F8 4C 05 03 
300R    note: INFINITE LOOP!

test8
300: A9 60 8D ED FD A2 00 BD 18 03 20 ED FD E8 E0 03 90 F5 A9 8D 20 ED FD 00 1A 2B 3C
300R

test8

"""
